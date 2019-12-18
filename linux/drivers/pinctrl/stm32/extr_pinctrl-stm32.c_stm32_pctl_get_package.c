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
struct stm32_pinctrl {scalar_t__ pkg; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static void stm32_pctl_get_package(struct device_node *np,
				   struct stm32_pinctrl *pctl)
{
	if (of_property_read_u32(np, "st,package", &pctl->pkg)) {
		pctl->pkg = 0;
		dev_warn(pctl->dev, "No package detected, use default one\n");
	} else {
		dev_dbg(pctl->dev, "package detected: %x\n", pctl->pkg);
	}
}