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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */

__attribute__((used)) static void ps3_sb_unmap_sg(struct device *_dev, struct scatterlist *sg,
	int nents, enum dma_data_direction direction, unsigned long attrs)
{
#if defined(CONFIG_PS3_DYNAMIC_DMA)
	BUG_ON("do");
#endif
}