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

/* Variables and functions */
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 scalar_t__ misc_registered ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  synth_device ; 
 int /*<<< orphan*/  synthu_device ; 

__attribute__((used)) static void softsynth_release(void)
{
	misc_deregister(&synth_device);
	misc_deregister(&synthu_device);
	misc_registered = 0;
	pr_info("unregistered /dev/softsynth\n");
	pr_info("unregistered /dev/softsynthu\n");
}