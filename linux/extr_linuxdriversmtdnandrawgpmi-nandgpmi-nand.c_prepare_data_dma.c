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
struct gpmi_nand_data {void const* data_buffer_dma; int /*<<< orphan*/  dev; struct scatterlist data_sgl; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,int) ; 
 int /*<<< orphan*/  object_is_on_stack (void const*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void const*,int) ; 
 scalar_t__ virt_addr_valid (void const*) ; 

bool prepare_data_dma(struct gpmi_nand_data *this, const void *buf, int len,
		      enum dma_data_direction dr)
{
	struct scatterlist *sgl = &this->data_sgl;
	int ret;

	/* first try to map the upper buffer directly */
	if (virt_addr_valid(buf) && !object_is_on_stack(buf)) {
		sg_init_one(sgl, buf, len);
		ret = dma_map_sg(this->dev, sgl, 1, dr);
		if (ret == 0)
			goto map_fail;

		return true;
	}

map_fail:
	/* We have to use our own DMA buffer. */
	sg_init_one(sgl, this->data_buffer_dma, len);

	if (dr == DMA_TO_DEVICE)
		memcpy(this->data_buffer_dma, buf, len);

	dma_map_sg(this->dev, sgl, 1, dr);

	return false;
}