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
struct nvkm_fb {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv50_fb {int /*<<< orphan*/  r100c08; scalar_t__ r100c08_page; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EFAULT ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ alloc_page (int) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nv50_fb* nv50_fb (struct nvkm_fb*) ; 

__attribute__((used)) static int
nv50_fb_oneinit(struct nvkm_fb *base)
{
	struct nv50_fb *fb = nv50_fb(base);
	struct nvkm_device *device = fb->base.subdev.device;

	fb->r100c08_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (fb->r100c08_page) {
		fb->r100c08 = dma_map_page(device->dev, fb->r100c08_page, 0,
					   PAGE_SIZE, DMA_BIDIRECTIONAL);
		if (dma_mapping_error(device->dev, fb->r100c08))
			return -EFAULT;
	}

	return 0;
}