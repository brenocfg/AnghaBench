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
struct bch_geometry {int /*<<< orphan*/  auxiliary_size; } ;
struct gpmi_nand_data {void* raw_buffer; int /*<<< orphan*/  auxiliary_virt; int /*<<< orphan*/  auxiliary_phys; int /*<<< orphan*/ * data_buffer_dma; int /*<<< orphan*/  nand; struct device* dev; struct bch_geometry bch_geometry; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpmi_free_dma_buffer (struct gpmi_nand_data*) ; 
 void* kzalloc (scalar_t__,int) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpmi_alloc_dma_buffer(struct gpmi_nand_data *this)
{
	struct bch_geometry *geo = &this->bch_geometry;
	struct device *dev = this->dev;
	struct mtd_info *mtd = nand_to_mtd(&this->nand);

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

	this->auxiliary_virt = dma_alloc_coherent(dev, geo->auxiliary_size,
					&this->auxiliary_phys, GFP_DMA);
	if (!this->auxiliary_virt)
		goto error_alloc;

	this->raw_buffer = kzalloc((mtd->writesize ?: PAGE_SIZE) + mtd->oobsize, GFP_KERNEL);
	if (!this->raw_buffer)
		goto error_alloc;

	return 0;

error_alloc:
	gpmi_free_dma_buffer(this);
	return -ENOMEM;
}