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
struct gpmi_nand_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int bch_set_geometry (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gpmi_alloc_dma_buffer (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_free_dma_buffer (struct gpmi_nand_data*) ; 

__attribute__((used)) static int gpmi_set_geometry(struct gpmi_nand_data *this)
{
	int ret;

	/* Free the temporary DMA memory for reading ID. */
	gpmi_free_dma_buffer(this);

	/* Set up the NFC geometry which is used by BCH. */
	ret = bch_set_geometry(this);
	if (ret) {
		dev_err(this->dev, "Error setting BCH geometry : %d\n", ret);
		return ret;
	}

	/* Alloc the new DMA buffers according to the pagesize and oobsize */
	return gpmi_alloc_dma_buffer(this);
}