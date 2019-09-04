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
struct thin_c {int dummy; } ;
struct dm_target {struct thin_c* private; } ;

/* Variables and functions */
 scalar_t__ dm_noflush_suspending (struct dm_target*) ; 
 int /*<<< orphan*/  do_noflush_start ; 
 int /*<<< orphan*/  noflush_work (struct thin_c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thin_presuspend(struct dm_target *ti)
{
	struct thin_c *tc = ti->private;

	if (dm_noflush_suspending(ti))
		noflush_work(tc, do_noflush_start);
}