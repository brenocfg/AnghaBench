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
 int /*<<< orphan*/  do_noflush_stop ; 
 int /*<<< orphan*/  noflush_work (struct thin_c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thin_postsuspend(struct dm_target *ti)
{
	struct thin_c *tc = ti->private;

	/*
	 * The dm_noflush_suspending flag has been cleared by now, so
	 * unfortunately we must always run this.
	 */
	noflush_work(tc, do_noflush_stop);
}