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
struct omapfb_info {scalar_t__ rotation_type; struct omapfb2_mem_region* region; struct omapfb2_device* fbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** vaddr; } ;
struct omapfb2_mem_region {scalar_t__ size; scalar_t__ alloc; scalar_t__ paddr; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/ * token; int /*<<< orphan*/  attrs; int /*<<< orphan*/  dma_handle; TYPE_1__ vrfb; int /*<<< orphan*/  map_count; } ;
struct omapfb2_device {int /*<<< orphan*/  dev; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 scalar_t__ OMAP_DSS_ROT_VRFB ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_vrfb_release_ctx (TYPE_1__*) ; 

__attribute__((used)) static void omapfb_free_fbmem(struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omapfb2_mem_region *rg;

	rg = ofbi->region;

	if (rg->token == NULL)
		return;

	WARN_ON(atomic_read(&rg->map_count));

	if (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) {
		/* unmap the 0 angle rotation */
		if (rg->vrfb.vaddr[0]) {
			iounmap(rg->vrfb.vaddr[0]);
			rg->vrfb.vaddr[0] = NULL;
		}

		omap_vrfb_release_ctx(&rg->vrfb);
	}

	dma_free_attrs(fbdev->dev, rg->size, rg->token, rg->dma_handle,
			rg->attrs);

	rg->token = NULL;
	rg->vaddr = NULL;
	rg->paddr = 0;
	rg->alloc = 0;
	rg->size = 0;
}