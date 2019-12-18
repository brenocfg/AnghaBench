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
typedef  int u8 ;
typedef  int u32 ;
struct msdc_host {int hs200_cmd_int_delay; int /*<<< orphan*/  dev; scalar_t__ base; scalar_t__ hs400_cmd_resp_sel_rising; } ;
struct msdc_delay_phase {int final_phase; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ timing; } ;
struct mmc_host {TYPE_1__ ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ MMC_TIMING_MMC_HS200 ; 
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 scalar_t__ MSDC_IOCON ; 
 int /*<<< orphan*/  MSDC_IOCON_RSPL ; 
 scalar_t__ MSDC_PAD_TUNE ; 
 int /*<<< orphan*/  MSDC_PAD_TUNE_CMDRRDLY ; 
 scalar_t__ PAD_CMD_TUNE ; 
 int /*<<< orphan*/  PAD_CMD_TUNE_RX_DLY3 ; 
 int PAD_DELAY_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct msdc_delay_phase get_best_delay (struct msdc_host*,int) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_send_tuning (struct mmc_host*,int,int*) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hs400_tune_response(struct mmc_host *mmc, u32 opcode)
{
	struct msdc_host *host = mmc_priv(mmc);
	u32 cmd_delay = 0;
	struct msdc_delay_phase final_cmd_delay = { 0,};
	u8 final_delay;
	int cmd_err;
	int i, j;

	/* select EMMC50 PAD CMD tune */
	sdr_set_bits(host->base + PAD_CMD_TUNE, BIT(0));

	if (mmc->ios.timing == MMC_TIMING_MMC_HS200 ||
	    mmc->ios.timing == MMC_TIMING_UHS_SDR104)
		sdr_set_field(host->base + MSDC_PAD_TUNE,
			      MSDC_PAD_TUNE_CMDRRDLY,
			      host->hs200_cmd_int_delay);

	if (host->hs400_cmd_resp_sel_rising)
		sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	else
		sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	for (i = 0 ; i < PAD_DELAY_MAX; i++) {
		sdr_set_field(host->base + PAD_CMD_TUNE,
			      PAD_CMD_TUNE_RX_DLY3, i);
		/*
		 * Using the same parameters, it may sometimes pass the test,
		 * but sometimes it may fail. To make sure the parameters are
		 * more stable, we test each set of parameters 3 times.
		 */
		for (j = 0; j < 3; j++) {
			mmc_send_tuning(mmc, opcode, &cmd_err);
			if (!cmd_err) {
				cmd_delay |= (1 << i);
			} else {
				cmd_delay &= ~(1 << i);
				break;
			}
		}
	}
	final_cmd_delay = get_best_delay(host, cmd_delay);
	sdr_set_field(host->base + PAD_CMD_TUNE, PAD_CMD_TUNE_RX_DLY3,
		      final_cmd_delay.final_phase);
	final_delay = final_cmd_delay.final_phase;

	dev_dbg(host->dev, "Final cmd pad delay: %x\n", final_delay);
	return final_delay == 0xff ? -EIO : 0;
}