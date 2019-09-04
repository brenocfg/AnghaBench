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
struct mtd_info {scalar_t__ oobsize; scalar_t__ writesize; } ;
struct bch_geometry {scalar_t__ payload_size; scalar_t__ auxiliary_size; } ;
struct gpmi_nand_data {scalar_t__ payload_phys; scalar_t__ auxiliary_phys; scalar_t__ payload_virt; scalar_t__ auxiliary_virt; scalar_t__ page_buffer_phys; scalar_t__ page_buffer_virt; void* raw_buffer; scalar_t__ page_buffer_size; int /*<<< orphan*/ * data_buffer_dma; int /*<<< orphan*/ * cmd_buffer; int /*<<< orphan*/  nand; struct device* dev; struct bch_geometry bch_geometry; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ dma_alloc_coherent (struct device*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  gpmi_free_dma_buffer (struct gpmi_nand_data*) ; 
 void* kzalloc (scalar_t__,int) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpmi_alloc_dma_buffer(struct gpmi_nand_data *this)
{
	struct bch_geometry *geo = &this->bch_geometry;
	struct device *dev = this->dev;
	struct mtd_info *mtd = nand_to_mtd(&this->nand);

	/* [1] Allocate a command buffer. PAGE_SIZE is enough. */
	this->cmd_buffer = kzalloc(PAGE_SIZE, GFP_DMA | GFP_KERNEL);
	if (this->cmd_buffer == NULL)
		goto error_alloc;

	/*
	 * [2] Allocate a read/write data buffer.
	 *     The gpmi_alloc_dma_buffer can be called twice.
	 *     We allocate a PAGE_SIZE length buffer if gpmi_alloc_dma_buffer
	 *     is called before the NAND identification; and we allocate a
	 *     buffer of the real NAND page size when the gpmi_alloc_dma_buffer
	 *     is called after.
	 */
	this->data_buffer_dma = kzalloc(mtd->writesize ?: PAGE_SIZE,
					GFP_DMA | GFP_KERNEL);
	if (this->data_buffer_dma == NULL)
		goto error_alloc;

	/*
	 * [3] Allocate the page buffer.
	 *
	 * Both the payload buffer and the auxiliary buffer must appear on
	 * 32-bit boundaries. We presume the size of the payload buffer is a
	 * power of two and is much larger than four, which guarantees the
	 * auxiliary buffer will appear on a 32-bit boundary.
	 */
	this->page_buffer_size = geo->payload_size + geo->auxiliary_size;
	this->page_buffer_virt = dma_alloc_coherent(dev, this->page_buffer_size,
					&this->page_buffer_phys, GFP_DMA);
	if (!this->page_buffer_virt)
		goto error_alloc;

	this->raw_buffer = kzalloc(mtd->writesize + mtd->oobsize, GFP_KERNEL);
	if (!this->raw_buffer)
		goto error_alloc;

	/* Slice up the page buffer. */
	this->payload_virt = this->page_buffer_virt;
	this->payload_phys = this->page_buffer_phys;
	this->auxiliary_virt = this->payload_virt + geo->payload_size;
	this->auxiliary_phys = this->payload_phys + geo->payload_size;
	return 0;

error_alloc:
	gpmi_free_dma_buffer(this);
	return -ENOMEM;
}