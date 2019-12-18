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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {void* emmc_top_cmd; void* emmc_top_control; void* pad_cmd_tune; void* pad_tune; void* iocon; } ;
struct msdc_host {int hs400_mode; scalar_t__ top_base; TYPE_2__ saved_tune_para; scalar_t__ base; int /*<<< orphan*/  dev; TYPE_1__* dev_comp; } ;
struct mmc_host {int dummy; } ;
struct TYPE_3__ {scalar_t__ hs400_tune; scalar_t__ async_fifo; scalar_t__ data_tune; scalar_t__ pad_tune_reg; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ EMMC_TOP_CMD ; 
 scalar_t__ EMMC_TOP_CONTROL ; 
 scalar_t__ MSDC_IOCON ; 
 int MSDC_IOCON_DSPL ; 
 int MSDC_IOCON_W_DSPL ; 
 scalar_t__ PAD_CMD_TUNE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hs400_tune_response (struct mmc_host*,scalar_t__) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  msdc_set_data_delay (struct msdc_host*,int /*<<< orphan*/ ) ; 
 int msdc_tune_data (struct mmc_host*,scalar_t__) ; 
 int msdc_tune_response (struct mmc_host*,scalar_t__) ; 
 int msdc_tune_together (struct mmc_host*,scalar_t__) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int) ; 

__attribute__((used)) static int msdc_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct msdc_host *host = mmc_priv(mmc);
	int ret;
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	if (host->dev_comp->data_tune && host->dev_comp->async_fifo) {
		ret = msdc_tune_together(mmc, opcode);
		if (host->hs400_mode) {
			sdr_clr_bits(host->base + MSDC_IOCON,
				     MSDC_IOCON_DSPL | MSDC_IOCON_W_DSPL);
			msdc_set_data_delay(host, 0);
		}
		goto tune_done;
	}
	if (host->hs400_mode &&
	    host->dev_comp->hs400_tune)
		ret = hs400_tune_response(mmc, opcode);
	else
		ret = msdc_tune_response(mmc, opcode);
	if (ret == -EIO) {
		dev_err(host->dev, "Tune response fail!\n");
		return ret;
	}
	if (host->hs400_mode == false) {
		ret = msdc_tune_data(mmc, opcode);
		if (ret == -EIO)
			dev_err(host->dev, "Tune data fail!\n");
	}

tune_done:
	host->saved_tune_para.iocon = readl(host->base + MSDC_IOCON);
	host->saved_tune_para.pad_tune = readl(host->base + tune_reg);
	host->saved_tune_para.pad_cmd_tune = readl(host->base + PAD_CMD_TUNE);
	if (host->top_base) {
		host->saved_tune_para.emmc_top_control = readl(host->top_base +
				EMMC_TOP_CONTROL);
		host->saved_tune_para.emmc_top_cmd = readl(host->top_base +
				EMMC_TOP_CMD);
	}
	return ret;
}