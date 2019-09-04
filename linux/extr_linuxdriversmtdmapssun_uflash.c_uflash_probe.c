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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int uflash_devinit (struct platform_device*,struct device_node*) ; 

__attribute__((used)) static int uflash_probe(struct platform_device *op)
{
	struct device_node *dp = op->dev.of_node;

	/* Flashprom must have the "user" property in order to
	 * be used by this driver.
	 */
	if (!of_find_property(dp, "user", NULL))
		return -ENODEV;

	return uflash_devinit(op, dp);
}