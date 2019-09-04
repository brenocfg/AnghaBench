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
typedef  int u16 ;
struct tiler_block {int dummy; } ;
struct omap_drm_usergart_entry {int /*<<< orphan*/  dma_addr; struct tiler_block* block; } ;
struct omap_drm_usergart {int height; int stride_pfn; struct omap_drm_usergart_entry* entry; void* slot_shift; void* height_shift; } ;
struct omap_drm_private {int has_dmm; struct omap_drm_usergart* usergart; } ;
struct drm_device {int /*<<< orphan*/  dev; struct omap_drm_private* dev_private; } ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  DBG (char*,int,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tiler_block*) ; 
 int NUM_USERGART_ENTRIES ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PTR_ERR (struct tiler_block*) ; 
 int const TILFMT_16BIT ; 
 int const TILFMT_32BIT ; 
 int const TILFMT_8BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmm_is_available () ; 
 void* ilog2 (int) ; 
 struct omap_drm_usergart* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiler_align (int const,int*,int*) ; 
 struct tiler_block* tiler_reserve_2d (int const,int,int,int) ; 
 int /*<<< orphan*/  tiler_ssptr (struct tiler_block*) ; 
 int tiler_stride (int const,int /*<<< orphan*/ ) ; 

void omap_gem_init(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;
	struct omap_drm_usergart *usergart;
	const enum tiler_fmt fmts[] = {
			TILFMT_8BIT, TILFMT_16BIT, TILFMT_32BIT
	};
	int i, j;

	if (!dmm_is_available()) {
		/* DMM only supported on OMAP4 and later, so this isn't fatal */
		dev_warn(dev->dev, "DMM not available, disable DMM support\n");
		return;
	}

	usergart = kcalloc(3, sizeof(*usergart), GFP_KERNEL);
	if (!usergart)
		return;

	/* reserve 4k aligned/wide regions for userspace mappings: */
	for (i = 0; i < ARRAY_SIZE(fmts); i++) {
		u16 h = 1, w = PAGE_SIZE >> i;

		tiler_align(fmts[i], &w, &h);
		/* note: since each region is 1 4kb page wide, and minimum
		 * number of rows, the height ends up being the same as the
		 * # of pages in the region
		 */
		usergart[i].height = h;
		usergart[i].height_shift = ilog2(h);
		usergart[i].stride_pfn = tiler_stride(fmts[i], 0) >> PAGE_SHIFT;
		usergart[i].slot_shift = ilog2((PAGE_SIZE / h) >> i);
		for (j = 0; j < NUM_USERGART_ENTRIES; j++) {
			struct omap_drm_usergart_entry *entry;
			struct tiler_block *block;

			entry = &usergart[i].entry[j];
			block = tiler_reserve_2d(fmts[i], w, h, PAGE_SIZE);
			if (IS_ERR(block)) {
				dev_err(dev->dev,
						"reserve failed: %d, %d, %ld\n",
						i, j, PTR_ERR(block));
				return;
			}
			entry->dma_addr = tiler_ssptr(block);
			entry->block = block;

			DBG("%d:%d: %dx%d: dma_addr=%pad stride=%d", i, j, w, h,
					&entry->dma_addr,
					usergart[i].stride_pfn << PAGE_SHIFT);
		}
	}

	priv->usergart = usergart;
	priv->has_dmm = true;
}