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
struct gpmi_nand_data {void const* data_buffer_dma; int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 int gpmi_raw_len_to_len (struct gpmi_nand_data*,int) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,int) ; 
 int /*<<< orphan*/  object_is_on_stack (void const*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void const*,int) ; 
 scalar_t__ virt_addr_valid (void const*) ; 

__attribute__((used)) static bool prepare_data_dma(struct gpmi_nand_data *this, const void *buf,
			     int raw_len, struct scatterlist *sgl,
			     enum dma_data_direction dr)
{
	int ret;
	int len = gpmi_raw_len_to_len(this, raw_len);

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

	if (dr == DMA_TO_DEVICE && buf != this->data_buffer_dma)
		memcpy(this->data_buffer_dma, buf, len);

	dma_map_sg(this->dev, sgl, 1, dr);

	return false;
}