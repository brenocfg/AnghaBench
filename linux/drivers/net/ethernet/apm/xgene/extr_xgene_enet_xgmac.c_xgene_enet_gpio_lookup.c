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
struct xgene_enet_pdata {void* sfp_rdy; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (void*) ; 
 void* gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_enet_gpio_lookup(struct xgene_enet_pdata *pdata)
{
	struct device *dev = &pdata->pdev->dev;

	pdata->sfp_rdy = gpiod_get(dev, "rxlos", GPIOD_IN);
	if (IS_ERR(pdata->sfp_rdy))
		pdata->sfp_rdy = gpiod_get(dev, "sfp", GPIOD_IN);

	if (IS_ERR(pdata->sfp_rdy))
		return -ENODEV;

	return 0;
}