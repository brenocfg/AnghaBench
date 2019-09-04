#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcm_iproc_i2c_dev {unsigned int bus_speed; TYPE_1__* device; scalar_t__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int TIM_CFG_MODE_400_SHIFT ; 
 scalar_t__ TIM_CFG_OFFSET ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,...) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bcm_iproc_i2c_cfg_speed(struct bcm_iproc_i2c_dev *iproc_i2c)
{
	unsigned int bus_speed;
	u32 val;
	int ret = of_property_read_u32(iproc_i2c->device->of_node,
				       "clock-frequency", &bus_speed);
	if (ret < 0) {
		dev_info(iproc_i2c->device,
			"unable to interpret clock-frequency DT property\n");
		bus_speed = 100000;
	}

	if (bus_speed < 100000) {
		dev_err(iproc_i2c->device, "%d Hz bus speed not supported\n",
			bus_speed);
		dev_err(iproc_i2c->device,
			"valid speeds are 100khz and 400khz\n");
		return -EINVAL;
	} else if (bus_speed < 400000) {
		bus_speed = 100000;
	} else {
		bus_speed = 400000;
	}

	iproc_i2c->bus_speed = bus_speed;
	val = readl(iproc_i2c->base + TIM_CFG_OFFSET);
	val &= ~(1 << TIM_CFG_MODE_400_SHIFT);
	val |= (bus_speed == 400000) << TIM_CFG_MODE_400_SHIFT;
	writel(val, iproc_i2c->base + TIM_CFG_OFFSET);

	dev_info(iproc_i2c->device, "bus set to %u Hz\n", bus_speed);

	return 0;
}