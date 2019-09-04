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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_map_sg (struct device*,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int,int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int cc_dma_map_sg(struct device *dev, struct scatterlist *sg, u32 nents,
			 enum dma_data_direction direction)
{
	u32 i, j;
	struct scatterlist *l_sg = sg;

	for (i = 0; i < nents; i++) {
		if (!l_sg)
			break;
		if (dma_map_sg(dev, l_sg, 1, direction) != 1) {
			dev_err(dev, "dma_map_page() sg buffer failed\n");
			goto err;
		}
		l_sg = sg_next(l_sg);
	}
	return nents;

err:
	/* Restore mapped parts */
	for (j = 0; j < i; j++) {
		if (!sg)
			break;
		dma_unmap_sg(dev, sg, 1, direction);
		sg = sg_next(sg);
	}
	return 0;
}