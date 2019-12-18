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
struct sdio_func {int enable_timeout; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_size; } ;
struct ath10k_sdio {TYPE_1__ mbox_info; struct sdio_func* func; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 unsigned char ATH10K_SDIO_DRIVE_DTSX_MASK ; 
 unsigned char ATH10K_SDIO_DRIVE_DTSX_TYPE_D ; 
 int /*<<< orphan*/  CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS ; 
 unsigned char CCCR_SDIO_ASYNC_INT_DELAY_MASK ; 
 unsigned char CCCR_SDIO_DRIVER_STRENGTH_ENABLE_A ; 
 int /*<<< orphan*/  CCCR_SDIO_DRIVER_STRENGTH_ENABLE_ADDR ; 
 unsigned char CCCR_SDIO_DRIVER_STRENGTH_ENABLE_C ; 
 unsigned char CCCR_SDIO_DRIVER_STRENGTH_ENABLE_D ; 
 int /*<<< orphan*/  CCCR_SDIO_IRQ_MODE_REG_SDIO3 ; 
 unsigned char FIELD_PREP (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  SDIO_CCCR_DRIVE_STRENGTH ; 
 unsigned char SDIO_IRQ_MODE_ASYNC_4BIT_IRQ_SDIO3 ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_sdio_func0_cmd52_rd_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int ath10k_sdio_func0_cmd52_wr_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_config(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct sdio_func *func = ar_sdio->func;
	unsigned char byte, asyncintdelay = 2;
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio configuration\n");

	sdio_claim_host(func);

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(func->card,
					      SDIO_CCCR_DRIVE_STRENGTH,
					      &byte);

	byte &= ~ATH10K_SDIO_DRIVE_DTSX_MASK;
	byte |= FIELD_PREP(ATH10K_SDIO_DRIVE_DTSX_MASK,
			   ATH10K_SDIO_DRIVE_DTSX_TYPE_D);

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      SDIO_CCCR_DRIVE_STRENGTH,
					      byte);

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(
		func->card,
		CCCR_SDIO_DRIVER_STRENGTH_ENABLE_ADDR,
		&byte);

	byte |= (CCCR_SDIO_DRIVER_STRENGTH_ENABLE_A |
		 CCCR_SDIO_DRIVER_STRENGTH_ENABLE_C |
		 CCCR_SDIO_DRIVER_STRENGTH_ENABLE_D);

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      CCCR_SDIO_DRIVER_STRENGTH_ENABLE_ADDR,
					      byte);
	if (ret) {
		ath10k_warn(ar, "failed to enable driver strength: %d\n", ret);
		goto out;
	}

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(func->card,
					      CCCR_SDIO_IRQ_MODE_REG_SDIO3,
					      &byte);

	byte |= SDIO_IRQ_MODE_ASYNC_4BIT_IRQ_SDIO3;

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      CCCR_SDIO_IRQ_MODE_REG_SDIO3,
					      byte);
	if (ret) {
		ath10k_warn(ar, "failed to enable 4-bit async irq mode: %d\n",
			    ret);
		goto out;
	}

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(func->card,
					      CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS,
					      &byte);

	byte &= ~CCCR_SDIO_ASYNC_INT_DELAY_MASK;
	byte |= FIELD_PREP(CCCR_SDIO_ASYNC_INT_DELAY_MASK, asyncintdelay);

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS,
					      byte);

	/* give us some time to enable, in ms */
	func->enable_timeout = 100;

	ret = sdio_set_block_size(func, ar_sdio->mbox_info.block_size);
	if (ret) {
		ath10k_warn(ar, "failed to set sdio block size to %d: %d\n",
			    ar_sdio->mbox_info.block_size, ret);
		goto out;
	}

out:
	sdio_release_host(func);
	return ret;
}