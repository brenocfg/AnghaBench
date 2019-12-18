#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_target {struct clone* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct clone {TYPE_1__ waker; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CLONE_HYDRATION_SUSPENDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_waker (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clone_resume(struct dm_target *ti)
{
	struct clone *clone = ti->private;

	clear_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags);
	do_waker(&clone->waker.work);
}