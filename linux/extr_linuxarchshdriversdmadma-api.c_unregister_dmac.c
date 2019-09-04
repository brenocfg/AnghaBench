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
struct dma_info {unsigned int nr_channels; int flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/  list; scalar_t__ channels; } ;

/* Variables and functions */
 int DMAC_CHANNELS_CONFIGURED ; 
 int /*<<< orphan*/  dma_remove_sysfs_files (scalar_t__,struct dma_info*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

void unregister_dmac(struct dma_info *info)
{
	unsigned int i;

	for (i = 0; i < info->nr_channels; i++)
		dma_remove_sysfs_files(info->channels + i, info);

	if (!(info->flags & DMAC_CHANNELS_CONFIGURED))
		kfree(info->channels);

	list_del(&info->list);
	platform_device_unregister(info->pdev);
}