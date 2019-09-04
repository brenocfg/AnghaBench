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
struct gpmi_nand_data {int /*<<< orphan*/  page_buffer_size; int /*<<< orphan*/ * page_buffer_virt; int /*<<< orphan*/ * raw_buffer; int /*<<< orphan*/ * data_buffer_dma; int /*<<< orphan*/ * cmd_buffer; int /*<<< orphan*/  page_buffer_phys; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ virt_addr_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpmi_free_dma_buffer(struct gpmi_nand_data *this)
{
	struct device *dev = this->dev;

	if (this->page_buffer_virt && virt_addr_valid(this->page_buffer_virt))
		dma_free_coherent(dev, this->page_buffer_size,
					this->page_buffer_virt,
					this->page_buffer_phys);
	kfree(this->cmd_buffer);
	kfree(this->data_buffer_dma);
	kfree(this->raw_buffer);

	this->cmd_buffer	= NULL;
	this->data_buffer_dma	= NULL;
	this->raw_buffer	= NULL;
	this->page_buffer_virt	= NULL;
	this->page_buffer_size	=  0;
}