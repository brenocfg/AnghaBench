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
struct dfl_feature_platform_data {TYPE_1__* dev; } ;
struct dfl_afu_dma_region {long length; int /*<<< orphan*/  pages; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 long PAGE_SHIFT ; 
 int /*<<< orphan*/  afu_dma_adjust_locked_vm (struct device*,long,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_all_pages (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void afu_dma_unpin_pages(struct dfl_feature_platform_data *pdata,
				struct dfl_afu_dma_region *region)
{
	long npages = region->length >> PAGE_SHIFT;
	struct device *dev = &pdata->dev->dev;

	put_all_pages(region->pages, npages);
	kfree(region->pages);
	afu_dma_adjust_locked_vm(dev, npages, false);

	dev_dbg(dev, "%ld pages unpinned\n", npages);
}