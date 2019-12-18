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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int ESDHC_TUNE_CTRL_MAX ; 
 int ESDHC_TUNE_CTRL_MIN ; 
 int ESDHC_TUNE_CTRL_STEP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  esdhc_post_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  esdhc_prepare_tuning (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_send_tuning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esdhc_executing_tuning(struct sdhci_host *host, u32 opcode)
{
	int min, max, avg, ret;

	/* find the mininum delay first which can pass tuning */
	min = ESDHC_TUNE_CTRL_MIN;
	while (min < ESDHC_TUNE_CTRL_MAX) {
		esdhc_prepare_tuning(host, min);
		if (!mmc_send_tuning(host->mmc, opcode, NULL))
			break;
		min += ESDHC_TUNE_CTRL_STEP;
	}

	/* find the maxinum delay which can not pass tuning */
	max = min + ESDHC_TUNE_CTRL_STEP;
	while (max < ESDHC_TUNE_CTRL_MAX) {
		esdhc_prepare_tuning(host, max);
		if (mmc_send_tuning(host->mmc, opcode, NULL)) {
			max -= ESDHC_TUNE_CTRL_STEP;
			break;
		}
		max += ESDHC_TUNE_CTRL_STEP;
	}

	/* use average delay to get the best timing */
	avg = (min + max) / 2;
	esdhc_prepare_tuning(host, avg);
	ret = mmc_send_tuning(host->mmc, opcode, NULL);
	esdhc_post_tuning(host);

	dev_dbg(mmc_dev(host->mmc), "tuning %s at 0x%x ret %d\n",
		ret ? "failed" : "passed", avg, ret);

	return ret;
}