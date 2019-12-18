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
struct bch_geometry {int /*<<< orphan*/  auxiliary_size; } ;
struct gpmi_nand_data {int /*<<< orphan*/ * raw_buffer; int /*<<< orphan*/ * data_buffer_dma; int /*<<< orphan*/  auxiliary_phys; int /*<<< orphan*/  auxiliary_virt; struct bch_geometry bch_geometry; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ virt_addr_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpmi_free_dma_buffer(struct gpmi_nand_data *this)
{
	struct device *dev = this->dev;
	struct bch_geometry *geo = &this->bch_geometry;

	if (this->auxiliary_virt && virt_addr_valid(this->auxiliary_virt))
		dma_free_coherent(dev, geo->auxiliary_size,
					this->auxiliary_virt,
					this->auxiliary_phys);
	kfree(this->data_buffer_dma);
	kfree(this->raw_buffer);

	this->data_buffer_dma	= NULL;
	this->raw_buffer	= NULL;
}