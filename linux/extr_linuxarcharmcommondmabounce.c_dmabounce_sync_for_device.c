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
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync_single_for_device ) (struct device*,int /*<<< orphan*/ ,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __dmabounce_sync_for_device (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 TYPE_1__ arm_dma_ops ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void dmabounce_sync_for_device(struct device *dev,
		dma_addr_t handle, size_t size, enum dma_data_direction dir)
{
	if (!__dmabounce_sync_for_device(dev, handle, size, dir))
		return;

	arm_dma_ops.sync_single_for_device(dev, handle, size, dir);
}