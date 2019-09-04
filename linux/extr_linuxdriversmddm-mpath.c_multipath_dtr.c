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
struct multipath {int dummy; } ;
struct dm_target {struct multipath* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_multipath_work (struct multipath*) ; 
 int /*<<< orphan*/  free_multipath (struct multipath*) ; 

__attribute__((used)) static void multipath_dtr(struct dm_target *ti)
{
	struct multipath *m = ti->private;

	flush_multipath_work(m);
	free_multipath(m);
}