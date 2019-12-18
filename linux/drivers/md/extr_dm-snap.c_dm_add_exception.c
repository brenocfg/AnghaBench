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
struct dm_exception_table_lock {int dummy; } ;
struct dm_exception {void* new_chunk; void* old_chunk; } ;
typedef  void* chunk_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dm_exception* alloc_completed_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_exception_table_lock (struct dm_exception_table_lock*) ; 
 int /*<<< orphan*/  dm_exception_table_lock_init (struct dm_snapshot*,void*,struct dm_exception_table_lock*) ; 
 int /*<<< orphan*/  dm_exception_table_unlock (struct dm_exception_table_lock*) ; 
 int /*<<< orphan*/  dm_insert_exception (int /*<<< orphan*/ *,struct dm_exception*) ; 

__attribute__((used)) static int dm_add_exception(void *context, chunk_t old, chunk_t new)
{
	struct dm_exception_table_lock lock;
	struct dm_snapshot *s = context;
	struct dm_exception *e;

	e = alloc_completed_exception(GFP_KERNEL);
	if (!e)
		return -ENOMEM;

	e->old_chunk = old;

	/* Consecutive_count is implicitly initialised to zero */
	e->new_chunk = new;

	/*
	 * Although there is no need to lock access to the exception tables
	 * here, if we don't then hlist_bl_add_head(), called by
	 * dm_insert_exception(), will complain about accessing the
	 * corresponding list without locking it first.
	 */
	dm_exception_table_lock_init(s, old, &lock);

	dm_exception_table_lock(&lock);
	dm_insert_exception(&s->complete, e);
	dm_exception_table_unlock(&lock);

	return 0;
}