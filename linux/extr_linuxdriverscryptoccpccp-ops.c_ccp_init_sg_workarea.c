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
typedef  scalar_t__ u64 ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct ccp_sg_workarea {scalar_t__ nents; int dma_dir; int /*<<< orphan*/  dma_count; struct device* dma_dev; struct scatterlist* dma_sg; scalar_t__ sg_used; scalar_t__ bytes_left; struct scatterlist* sg; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_map_sg (struct device*,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  memset (struct ccp_sg_workarea*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sg_nents_for_len (struct scatterlist*,scalar_t__) ; 

__attribute__((used)) static int ccp_init_sg_workarea(struct ccp_sg_workarea *wa, struct device *dev,
				struct scatterlist *sg, u64 len,
				enum dma_data_direction dma_dir)
{
	memset(wa, 0, sizeof(*wa));

	wa->sg = sg;
	if (!sg)
		return 0;

	wa->nents = sg_nents_for_len(sg, len);
	if (wa->nents < 0)
		return wa->nents;

	wa->bytes_left = len;
	wa->sg_used = 0;

	if (len == 0)
		return 0;

	if (dma_dir == DMA_NONE)
		return 0;

	wa->dma_sg = sg;
	wa->dma_dev = dev;
	wa->dma_dir = dma_dir;
	wa->dma_count = dma_map_sg(dev, sg, wa->nents, dma_dir);
	if (!wa->dma_count)
		return -ENOMEM;

	return 0;
}