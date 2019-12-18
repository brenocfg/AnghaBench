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
struct TYPE_2__ {int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct umc_dev {TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 struct umc_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umc_bus_type ; 
 int /*<<< orphan*/  umc_device_release ; 

struct umc_dev *umc_device_create(struct device *parent, int n)
{
	struct umc_dev *umc;

	umc = kzalloc(sizeof(struct umc_dev), GFP_KERNEL);
	if (umc) {
		dev_set_name(&umc->dev, "%s-%d", dev_name(parent), n);
		umc->dev.parent  = parent;
		umc->dev.bus     = &umc_bus_type;
		umc->dev.release = umc_device_release;

		umc->dev.dma_mask = parent->dma_mask;
	}
	return umc;
}