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
typedef  int u32 ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int SD_OCR_CCS ; 
 int SD_OCR_S18R ; 
 int SD_OCR_XPC ; 
 int /*<<< orphan*/  mmc_go_idle (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 scalar_t__ mmc_host_uhs (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int mmc_send_app_op_cond (struct mmc_host*,int,int*) ; 
 int mmc_send_cid (struct mmc_host*,int*) ; 
 int mmc_send_if_cond (struct mmc_host*,int) ; 
 int mmc_set_uhs_voltage (struct mmc_host*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int sd_get_host_max_current (struct mmc_host*) ; 

int mmc_sd_get_cid(struct mmc_host *host, u32 ocr, u32 *cid, u32 *rocr)
{
	int err;
	u32 max_current;
	int retries = 10;
	u32 pocr = ocr;

try_again:
	if (!retries) {
		ocr &= ~SD_OCR_S18R;
		pr_warn("%s: Skipping voltage switch\n", mmc_hostname(host));
	}

	/*
	 * Since we're changing the OCR value, we seem to
	 * need to tell some cards to go back to the idle
	 * state.  We wait 1ms to give cards time to
	 * respond.
	 */
	mmc_go_idle(host);

	/*
	 * If SD_SEND_IF_COND indicates an SD 2.0
	 * compliant card and we should set bit 30
	 * of the ocr to indicate that we can handle
	 * block-addressed SDHC cards.
	 */
	err = mmc_send_if_cond(host, ocr);
	if (!err)
		ocr |= SD_OCR_CCS;

	/*
	 * If the host supports one of UHS-I modes, request the card
	 * to switch to 1.8V signaling level. If the card has failed
	 * repeatedly to switch however, skip this.
	 */
	if (retries && mmc_host_uhs(host))
		ocr |= SD_OCR_S18R;

	/*
	 * If the host can supply more than 150mA at current voltage,
	 * XPC should be set to 1.
	 */
	max_current = sd_get_host_max_current(host);
	if (max_current > 150)
		ocr |= SD_OCR_XPC;

	err = mmc_send_app_op_cond(host, ocr, rocr);
	if (err)
		return err;

	/*
	 * In case CCS and S18A in the response is set, start Signal Voltage
	 * Switch procedure. SPI mode doesn't support CMD11.
	 */
	if (!mmc_host_is_spi(host) && rocr &&
	   ((*rocr & 0x41000000) == 0x41000000)) {
		err = mmc_set_uhs_voltage(host, pocr);
		if (err == -EAGAIN) {
			retries--;
			goto try_again;
		} else if (err) {
			retries = 0;
			goto try_again;
		}
	}

	err = mmc_send_cid(host, cid);
	return err;
}