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
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int pasic3_read_register (struct device*,int) ; 
 int /*<<< orphan*/  pasic3_write_register (struct device*,int,int) ; 

__attribute__((used)) static int ds1wm_disable(struct platform_device *pdev)
{
	struct device *dev = pdev->dev.parent;
	int c;

	c = pasic3_read_register(dev, 0x28);
	pasic3_write_register(dev, 0x28, c | 0x80);

	dev_dbg(dev, "DS1WM OWM_EN high (inactive) %02x\n", c | 0x80);
	return 0;
}