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
struct fw_device {int generation; int /*<<< orphan*/  node_id; TYPE_2__* card; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* enable_phys_dma ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int fw_device_enable_phys_dma(struct fw_device *device)
{
	int generation = device->generation;

	/* device->node_id, accessed below, must not be older than generation */
	smp_rmb();

	return device->card->driver->enable_phys_dma(device->card,
						     device->node_id,
						     generation);
}