#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sdhci_host {int /*<<< orphan*/  quirks; TYPE_2__* mmc; } ;
struct esdhc_platform_data {scalar_t__ wp_type; int cd_type; int max_bus_width; } ;
struct pltfm_imx_data {struct esdhc_platform_data boarddata; } ;
struct platform_device {int dummy; } ;
struct TYPE_6__ {int caps; int /*<<< orphan*/  caps2; TYPE_1__* parent; } ;
struct TYPE_5__ {scalar_t__ platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ESDHC_CD_CONTROLLER 131 
#define  ESDHC_CD_GPIO 130 
#define  ESDHC_CD_NONE 129 
#define  ESDHC_CD_PERMANENT 128 
 scalar_t__ ESDHC_WP_GPIO ; 
 int /*<<< orphan*/  MMC_CAP2_RO_ACTIVE_HIGH ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int /*<<< orphan*/  SDHCI_QUIRK_FORCE_1_BIT_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 
 int mmc_gpiod_request_cd (TYPE_2__*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmc_gpiod_request_ro (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdhci_esdhc_imx_probe_nondt(struct platform_device *pdev,
			 struct sdhci_host *host,
			 struct pltfm_imx_data *imx_data)
{
	struct esdhc_platform_data *boarddata = &imx_data->boarddata;
	int err;

	if (!host->mmc->parent->platform_data) {
		dev_err(mmc_dev(host->mmc), "no board data!\n");
		return -EINVAL;
	}

	imx_data->boarddata = *((struct esdhc_platform_data *)
				host->mmc->parent->platform_data);
	/* write_protect */
	if (boarddata->wp_type == ESDHC_WP_GPIO) {
		err = mmc_gpiod_request_ro(host->mmc, "wp", 0, 0, NULL);
		if (err) {
			dev_err(mmc_dev(host->mmc),
				"failed to request write-protect gpio!\n");
			return err;
		}
		host->mmc->caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;
	}

	/* card_detect */
	switch (boarddata->cd_type) {
	case ESDHC_CD_GPIO:
		err = mmc_gpiod_request_cd(host->mmc, "cd", 0, false, 0, NULL);
		if (err) {
			dev_err(mmc_dev(host->mmc),
				"failed to request card-detect gpio!\n");
			return err;
		}
		/* fall through */

	case ESDHC_CD_CONTROLLER:
		/* we have a working card_detect back */
		host->quirks &= ~SDHCI_QUIRK_BROKEN_CARD_DETECTION;
		break;

	case ESDHC_CD_PERMANENT:
		host->mmc->caps |= MMC_CAP_NONREMOVABLE;
		break;

	case ESDHC_CD_NONE:
		break;
	}

	switch (boarddata->max_bus_width) {
	case 8:
		host->mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA;
		break;
	case 4:
		host->mmc->caps |= MMC_CAP_4_BIT_DATA;
		break;
	case 1:
	default:
		host->quirks |= SDHCI_QUIRK_FORCE_1_BIT_DATA;
		break;
	}

	return 0;
}