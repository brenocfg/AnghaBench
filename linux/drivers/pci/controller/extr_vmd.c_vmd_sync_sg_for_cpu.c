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
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  to_vmd_dev (struct device*) ; 

__attribute__((used)) static void vmd_sync_sg_for_cpu(struct device *dev, struct scatterlist *sg,
				int nents, enum dma_data_direction dir)
{
	dma_sync_sg_for_cpu(to_vmd_dev(dev), sg, nents, dir);
}