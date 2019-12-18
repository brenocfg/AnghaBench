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
struct dm_snapshot {int /*<<< orphan*/  pending_exceptions_count; int /*<<< orphan*/  pending_pool; } ;
struct dm_snap_pending_exception {struct dm_snapshot* snap; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct dm_snap_pending_exception*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void free_pending_exception(struct dm_snap_pending_exception *pe)
{
	struct dm_snapshot *s = pe->snap;

	mempool_free(pe, &s->pending_pool);
	smp_mb__before_atomic();
	atomic_dec(&s->pending_exceptions_count);
}