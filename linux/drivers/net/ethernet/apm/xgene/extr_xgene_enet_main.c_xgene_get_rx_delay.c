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
struct xgene_enet_pdata {int rx_delay; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 

__attribute__((used)) static int xgene_get_rx_delay(struct xgene_enet_pdata *pdata)
{
	struct device *dev = &pdata->pdev->dev;
	int delay, ret;

	ret = device_property_read_u32(dev, "rx-delay", &delay);
	if (ret) {
		pdata->rx_delay = 2;
		return 0;
	}

	if (delay < 0 || delay > 7) {
		dev_err(dev, "Invalid rx-delay specified\n");
		return -EINVAL;
	}

	pdata->rx_delay = delay;

	return 0;
}