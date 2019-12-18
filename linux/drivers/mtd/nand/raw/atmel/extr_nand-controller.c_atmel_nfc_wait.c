#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  smc; } ;
struct TYPE_4__ {int wait; int errors; } ;
struct atmel_hsmc_nand_controller {TYPE_1__ base; TYPE_2__ op; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HSMC_NFC_IDR ; 
 int /*<<< orphan*/  ATMEL_HSMC_NFC_IER ; 
 int /*<<< orphan*/  ATMEL_HSMC_NFC_SR ; 
 int ATMEL_HSMC_NFC_SR_AWB ; 
 int ATMEL_HSMC_NFC_SR_DTOE ; 
 int ATMEL_HSMC_NFC_SR_ERRORS ; 
 int ATMEL_HSMC_NFC_SR_NFCASE ; 
 int ATMEL_HSMC_NFC_SR_UNDEF ; 
 unsigned int DEFAULT_TIMEOUT_MS ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  atmel_nfc_op_done (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nfc_wait(struct atmel_hsmc_nand_controller *nc, bool poll,
			  unsigned int timeout_ms)
{
	int ret;

	if (!timeout_ms)
		timeout_ms = DEFAULT_TIMEOUT_MS;

	if (poll) {
		u32 status;

		ret = regmap_read_poll_timeout(nc->base.smc,
					       ATMEL_HSMC_NFC_SR, status,
					       atmel_nfc_op_done(&nc->op,
								 status),
					       0, timeout_ms * 1000);
	} else {
		init_completion(&nc->complete);
		regmap_write(nc->base.smc, ATMEL_HSMC_NFC_IER,
			     nc->op.wait | ATMEL_HSMC_NFC_SR_ERRORS);
		ret = wait_for_completion_timeout(&nc->complete,
						msecs_to_jiffies(timeout_ms));
		if (!ret)
			ret = -ETIMEDOUT;
		else
			ret = 0;

		regmap_write(nc->base.smc, ATMEL_HSMC_NFC_IDR, 0xffffffff);
	}

	if (nc->op.errors & ATMEL_HSMC_NFC_SR_DTOE) {
		dev_err(nc->base.dev, "Waiting NAND R/B Timeout\n");
		ret = -ETIMEDOUT;
	}

	if (nc->op.errors & ATMEL_HSMC_NFC_SR_UNDEF) {
		dev_err(nc->base.dev, "Access to an undefined area\n");
		ret = -EIO;
	}

	if (nc->op.errors & ATMEL_HSMC_NFC_SR_AWB) {
		dev_err(nc->base.dev, "Access while busy\n");
		ret = -EIO;
	}

	if (nc->op.errors & ATMEL_HSMC_NFC_SR_NFCASE) {
		dev_err(nc->base.dev, "Wrong access size\n");
		ret = -EIO;
	}

	return ret;
}