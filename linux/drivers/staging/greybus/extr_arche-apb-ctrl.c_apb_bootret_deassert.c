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
struct device {int dummy; } ;
struct arche_apb_ctrl_drvdata {int /*<<< orphan*/  boot_ret; } ;

/* Variables and functions */
 struct arche_apb_ctrl_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apb_bootret_deassert(struct device *dev)
{
	struct arche_apb_ctrl_drvdata *apb = dev_get_drvdata(dev);

	gpiod_set_value(apb->boot_ret, 0);
}