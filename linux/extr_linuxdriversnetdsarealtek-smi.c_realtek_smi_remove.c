#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct realtek_smi {int /*<<< orphan*/  reset; TYPE_2__* slave_mii_bus; int /*<<< orphan*/  ds; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct realtek_smi* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realtek_smi_remove(struct platform_device *pdev)
{
	struct realtek_smi *smi = dev_get_drvdata(&pdev->dev);

	dsa_unregister_switch(smi->ds);
	if (smi->slave_mii_bus)
		of_node_put(smi->slave_mii_bus->dev.of_node);
	gpiod_set_value(smi->reset, 1);

	return 0;
}