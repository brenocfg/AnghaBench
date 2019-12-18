#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int number; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dev; } ;
struct TYPE_7__ {TYPE_1__ pinmux; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 TYPE_2__ aspeed_g5_pinctrl_data ; 
 int /*<<< orphan*/  aspeed_g5_pinctrl_desc ; 
 TYPE_3__* aspeed_g5_pins ; 
 int aspeed_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int aspeed_g5_pinctrl_probe(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(aspeed_g5_pins); i++)
		aspeed_g5_pins[i].number = i;

	aspeed_g5_pinctrl_data.pinmux.dev = &pdev->dev;

	return aspeed_pinctrl_probe(pdev, &aspeed_g5_pinctrl_desc,
			&aspeed_g5_pinctrl_data);
}