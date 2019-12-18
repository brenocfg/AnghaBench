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
struct work_struct {int dummy; } ;
struct dm_bio_prison_v2 {int /*<<< orphan*/  wq; } ;
struct dm_bio_prison_cell_v2 {struct work_struct* quiesce_continuation; int /*<<< orphan*/  shared_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 

__attribute__((used)) static void __quiesce(struct dm_bio_prison_v2 *prison,
		      struct dm_bio_prison_cell_v2 *cell,
		      struct work_struct *continuation)
{
	if (!cell->shared_count)
		queue_work(prison->wq, continuation);
	else
		cell->quiesce_continuation = continuation;
}