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
struct sa1100fb_mach_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sa11x0_register_device (int /*<<< orphan*/ *,struct sa1100fb_mach_info*) ; 
 int /*<<< orphan*/  sa11x0fb_device ; 

void sa11x0_register_lcd(struct sa1100fb_mach_info *inf)
{
	sa11x0_register_device(&sa11x0fb_device, inf);
}