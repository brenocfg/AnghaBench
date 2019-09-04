#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct amba_device {TYPE_2__ dev; TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  amba_bustype ; 
 int /*<<< orphan*/  amba_device_release ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 

__attribute__((used)) static void amba_device_initialize(struct amba_device *dev, const char *name)
{
	device_initialize(&dev->dev);
	if (name)
		dev_set_name(&dev->dev, "%s", name);
	dev->dev.release = amba_device_release;
	dev->dev.bus = &amba_bustype;
	dev->dev.dma_mask = &dev->dev.coherent_dma_mask;
	dev->res.name = dev_name(&dev->dev);
}