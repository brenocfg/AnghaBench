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
struct imx214 {TYPE_1__* supplies; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 unsigned int IMX214_NUM_SUPPLIES ; 
 int devm_regulator_bulk_get (struct device*,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/ * imx214_supply_name ; 

__attribute__((used)) static int imx214_get_regulators(struct device *dev, struct imx214 *imx214)
{
	unsigned int i;

	for (i = 0; i < IMX214_NUM_SUPPLIES; i++)
		imx214->supplies[i].supply = imx214_supply_name[i];

	return devm_regulator_bulk_get(dev, IMX214_NUM_SUPPLIES,
				       imx214->supplies);
}