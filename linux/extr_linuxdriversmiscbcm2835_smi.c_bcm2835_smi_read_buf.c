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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {scalar_t__ data_width; } ;
struct bcm2835_smi_instance {int /*<<< orphan*/  transaction_lock; int /*<<< orphan*/  dev; TYPE_1__ settings; int /*<<< orphan*/  buffer_sgl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 size_t DMA_THRESHOLD_BYTES ; 
 scalar_t__ SMI_WIDTH_8BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  smi_dma_read_sgl (struct bcm2835_smi_instance*,struct scatterlist*,int,size_t) ; 
 int /*<<< orphan*/  smi_dump_context_labelled (struct bcm2835_smi_instance*,char*) ; 
 int /*<<< orphan*/  smi_read_fifo (struct bcm2835_smi_instance*,int /*<<< orphan*/ *,size_t) ; 
 void* smi_read_single_word (struct bcm2835_smi_instance*) ; 
 struct scatterlist* smi_scatterlist_from_buffer (struct bcm2835_smi_instance*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bcm2835_smi_read_buf(struct bcm2835_smi_instance *inst,
	void *buf, size_t n_bytes)
{

	/* SMI is inherently 32-bit, which causes surprising amounts of mess
	   for bytes % 4 != 0. Easiest to avoid this mess altogether
	   by handling remainder separately. */
	int odd_bytes = n_bytes & 0x3;

	spin_lock(&inst->transaction_lock);
	n_bytes -= odd_bytes;
	if (n_bytes > DMA_THRESHOLD_BYTES) {
		dma_addr_t phy_addr = dma_map_single(inst->dev,
						     buf, n_bytes,
						     DMA_DEV_TO_MEM);
		struct scatterlist *sgl = smi_scatterlist_from_buffer(
			inst, phy_addr, n_bytes,
			&inst->buffer_sgl);
		if (!sgl) {
			smi_dump_context_labelled(inst,
			"Error: could not create scatterlist for read!");
			goto out;
		}
		smi_dma_read_sgl(inst, sgl, 1, n_bytes);
		dma_unmap_single(inst->dev, phy_addr, n_bytes, DMA_DEV_TO_MEM);
	} else if (n_bytes) {
		smi_read_fifo(inst, (uint32_t *)buf, n_bytes);
	}
	buf += n_bytes;

	if (inst->settings.data_width == SMI_WIDTH_8BIT) {
		while (odd_bytes--)
			*((uint8_t *) (buf++)) = smi_read_single_word(inst);
	} else {
		while (odd_bytes >= 2) {
			*(uint16_t *) buf = smi_read_single_word(inst);
			buf += 2;
			odd_bytes -= 2;
		}
		if (odd_bytes) {
			dev_err(inst->dev,
		"WARNING: odd number of bytes specified for wide transfer.");
			dev_err(inst->dev,
		"At least one byte dropped as a result.");
			dump_stack();
		}
	}
out:
	spin_unlock(&inst->transaction_lock);
}