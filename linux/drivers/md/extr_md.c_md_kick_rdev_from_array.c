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
struct md_rdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  export_rdev (struct md_rdev*) ; 
 int /*<<< orphan*/  unbind_rdev_from_array (struct md_rdev*) ; 

void md_kick_rdev_from_array(struct md_rdev *rdev)
{
	unbind_rdev_from_array(rdev);
	export_rdev(rdev);
}