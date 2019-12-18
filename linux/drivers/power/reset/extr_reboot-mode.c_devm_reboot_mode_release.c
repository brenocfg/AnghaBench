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
struct reboot_mode_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reboot_mode_unregister (struct reboot_mode_driver*) ; 

__attribute__((used)) static void devm_reboot_mode_release(struct device *dev, void *res)
{
	reboot_mode_unregister(*(struct reboot_mode_driver **)res);
}