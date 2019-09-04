#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vsp1_device {int /*<<< orphan*/  bus_master; } ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct vsp1_device* dev_get_drvdata (struct device*) ; 
 int dma_map_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vsp1_du_map_sg(struct device *dev, struct sg_table *sgt)
{
	struct vsp1_device *vsp1 = dev_get_drvdata(dev);

	/*
	 * As all the buffers allocated by the DU driver are coherent, we can
	 * skip cache sync. This will need to be revisited when support for
	 * non-coherent buffers will be added to the DU driver.
	 */
	return dma_map_sg_attrs(vsp1->bus_master, sgt->sgl, sgt->nents,
				DMA_TO_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
}