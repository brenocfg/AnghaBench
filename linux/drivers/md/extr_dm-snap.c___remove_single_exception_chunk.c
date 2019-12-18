#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dm_snapshot {int /*<<< orphan*/  complete; } ;
struct dm_exception {scalar_t__ old_chunk; int /*<<< orphan*/  new_chunk; } ;
typedef  scalar_t__ chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,unsigned long long,...) ; 
 int EINVAL ; 
 scalar_t__ dm_consecutive_chunk_count (struct dm_exception*) ; 
 int /*<<< orphan*/  dm_consecutive_chunk_count_dec (struct dm_exception*) ; 
 struct dm_exception* dm_lookup_exception (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dm_remove_exception (struct dm_exception*) ; 
 int /*<<< orphan*/  free_completed_exception (struct dm_exception*) ; 

__attribute__((used)) static int __remove_single_exception_chunk(struct dm_snapshot *s,
					   chunk_t old_chunk)
{
	struct dm_exception *e;

	e = dm_lookup_exception(&s->complete, old_chunk);
	if (!e) {
		DMERR("Corruption detected: exception for block %llu is "
		      "on disk but not in memory",
		      (unsigned long long)old_chunk);
		return -EINVAL;
	}

	/*
	 * If this is the only chunk using this exception, remove exception.
	 */
	if (!dm_consecutive_chunk_count(e)) {
		dm_remove_exception(e);
		free_completed_exception(e);
		return 0;
	}

	/*
	 * The chunk may be either at the beginning or the end of a
	 * group of consecutive chunks - never in the middle.  We are
	 * removing chunks in the opposite order to that in which they
	 * were added, so this should always be true.
	 * Decrement the consecutive chunk counter and adjust the
	 * starting point if necessary.
	 */
	if (old_chunk == e->old_chunk) {
		e->old_chunk++;
		e->new_chunk++;
	} else if (old_chunk != e->old_chunk +
		   dm_consecutive_chunk_count(e)) {
		DMERR("Attempt to merge block %llu from the "
		      "middle of a chunk range [%llu - %llu]",
		      (unsigned long long)old_chunk,
		      (unsigned long long)e->old_chunk,
		      (unsigned long long)
		      e->old_chunk + dm_consecutive_chunk_count(e));
		return -EINVAL;
	}

	dm_consecutive_chunk_count_dec(e);

	return 0;
}