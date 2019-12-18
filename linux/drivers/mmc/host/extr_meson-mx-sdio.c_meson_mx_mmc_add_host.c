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
struct mmc_host {int max_blk_size; int caps; int /*<<< orphan*/ * ops; void* f_max; void* f_min; void* max_blk_count; int /*<<< orphan*/  max_req_size; int /*<<< orphan*/  max_seg_size; } ;
struct meson_mx_mmc_host {int /*<<< orphan*/  parent_clk; int /*<<< orphan*/  cfg_div_clk; int /*<<< orphan*/  slot_id; struct mmc_host* mmc; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int EINVAL ; 
 void* FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MESON_MX_SDIO_BOUNCE_REQ_SIZE ; 
 int /*<<< orphan*/  MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_MAX_SLOTS ; 
 int MESON_MX_SDIO_RESPONSE_CRC16_BITS ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK ; 
 int MMC_CAP_CMD23 ; 
 int MMC_CAP_ERASE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 void* clk_round_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  meson_mx_mmc_ops ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct device* mmc_dev (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 int mmc_regulator_get_supply (struct mmc_host*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_mx_mmc_add_host(struct meson_mx_mmc_host *host)
{
	struct mmc_host *mmc = host->mmc;
	struct device *slot_dev = mmc_dev(mmc);
	int ret;

	if (of_property_read_u32(slot_dev->of_node, "reg", &host->slot_id)) {
		dev_err(slot_dev, "missing 'reg' property\n");
		return -EINVAL;
	}

	if (host->slot_id >= MESON_MX_SDIO_MAX_SLOTS) {
		dev_err(slot_dev, "invalid 'reg' property value %d\n",
			host->slot_id);
		return -EINVAL;
	}

	/* Get regulators and the supported OCR mask */
	ret = mmc_regulator_get_supply(mmc);
	if (ret)
		return ret;

	mmc->max_req_size = MESON_MX_SDIO_BOUNCE_REQ_SIZE;
	mmc->max_seg_size = mmc->max_req_size;
	mmc->max_blk_count =
		FIELD_GET(MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK,
			  0xffffffff);
	mmc->max_blk_size = FIELD_GET(MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK,
				      0xffffffff);
	mmc->max_blk_size -= (4 * MESON_MX_SDIO_RESPONSE_CRC16_BITS);
	mmc->max_blk_size /= BITS_PER_BYTE;

	/* Get the min and max supported clock rates */
	mmc->f_min = clk_round_rate(host->cfg_div_clk, 1);
	mmc->f_max = clk_round_rate(host->cfg_div_clk,
				    clk_get_rate(host->parent_clk));

	mmc->caps |= MMC_CAP_ERASE | MMC_CAP_CMD23;
	mmc->ops = &meson_mx_mmc_ops;

	ret = mmc_of_parse(mmc);
	if (ret)
		return ret;

	ret = mmc_add_host(mmc);
	if (ret)
		return ret;

	return 0;
}