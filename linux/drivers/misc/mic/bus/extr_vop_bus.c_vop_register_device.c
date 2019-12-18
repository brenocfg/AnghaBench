#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct vop_hw_ops {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct dma_map_ops const* dma_ops; struct device* parent; } ;
struct TYPE_6__ {int device; int /*<<< orphan*/  vendor; } ;
struct vop_device {TYPE_2__ dev; void* index; struct dma_chan* dma_ch; struct mic_mw* aper; void* dnode; struct vop_hw_ops* hw_ops; TYPE_1__ id; } ;
struct mic_mw {int dummy; } ;
struct dma_map_ops {int dummy; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 struct vop_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VOP_DEV_ANY_ID ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,void*) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_set_mask (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct vop_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  vop_bus ; 
 int /*<<< orphan*/  vop_release_dev ; 

struct vop_device *
vop_register_device(struct device *pdev, int id,
		    const struct dma_map_ops *dma_ops,
		    struct vop_hw_ops *hw_ops, u8 dnode, struct mic_mw *aper,
		    struct dma_chan *chan)
{
	int ret;
	struct vop_device *vdev;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev)
		return ERR_PTR(-ENOMEM);

	vdev->dev.parent = pdev;
	vdev->id.device = id;
	vdev->id.vendor = VOP_DEV_ANY_ID;
	vdev->dev.dma_ops = dma_ops;
	vdev->dev.dma_mask = &vdev->dev.coherent_dma_mask;
	dma_set_mask(&vdev->dev, DMA_BIT_MASK(64));
	vdev->dev.release = vop_release_dev;
	vdev->hw_ops = hw_ops;
	vdev->dev.bus = &vop_bus;
	vdev->dnode = dnode;
	vdev->aper = aper;
	vdev->dma_ch = chan;
	vdev->index = dnode - 1;
	dev_set_name(&vdev->dev, "vop-dev%u", vdev->index);
	/*
	 * device_register() causes the bus infrastructure to look for a
	 * matching driver.
	 */
	ret = device_register(&vdev->dev);
	if (ret)
		goto free_vdev;
	return vdev;
free_vdev:
	put_device(&vdev->dev);
	return ERR_PTR(ret);
}