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
struct stm32_fmc2_nfc {int /*<<< orphan*/  dma_ecc_complete; int /*<<< orphan*/  dma_data_complete; int /*<<< orphan*/  dma_data_sg; int /*<<< orphan*/  ecc_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_ecc_sg; void* dma_ecc_ch; void* dma_rx_ch; void* dma_tx_ch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FMC2_MAX_ECC_BUF_LEN ; 
 int /*<<< orphan*/  FMC2_MAX_SG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dma_request_slave_channel (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int sg_alloc_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_fmc2_dma_setup(struct stm32_fmc2_nfc *fmc2)
{
	int ret;

	fmc2->dma_tx_ch = dma_request_slave_channel(fmc2->dev, "tx");
	fmc2->dma_rx_ch = dma_request_slave_channel(fmc2->dev, "rx");
	fmc2->dma_ecc_ch = dma_request_slave_channel(fmc2->dev, "ecc");

	if (!fmc2->dma_tx_ch || !fmc2->dma_rx_ch || !fmc2->dma_ecc_ch) {
		dev_warn(fmc2->dev, "DMAs not defined in the device tree, polling mode is used\n");
		return 0;
	}

	ret = sg_alloc_table(&fmc2->dma_ecc_sg, FMC2_MAX_SG, GFP_KERNEL);
	if (ret)
		return ret;

	/* Allocate a buffer to store ECC status registers */
	fmc2->ecc_buf = devm_kzalloc(fmc2->dev, FMC2_MAX_ECC_BUF_LEN,
				     GFP_KERNEL);
	if (!fmc2->ecc_buf)
		return -ENOMEM;

	ret = sg_alloc_table(&fmc2->dma_data_sg, FMC2_MAX_SG, GFP_KERNEL);
	if (ret)
		return ret;

	init_completion(&fmc2->dma_data_complete);
	init_completion(&fmc2->dma_ecc_complete);

	return 0;
}