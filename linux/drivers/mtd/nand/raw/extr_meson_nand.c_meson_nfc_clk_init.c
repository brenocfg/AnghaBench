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
struct meson_nfc {void* core_clk; void* device_clk; void* phase_tx; int /*<<< orphan*/  dev; void* phase_rx; int /*<<< orphan*/  reg_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SELECT_NAND ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int clk_set_rate (void*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_nfc_clk_init(struct meson_nfc *nfc)
{
	int ret;

	/* request core clock */
	nfc->core_clk = devm_clk_get(nfc->dev, "core");
	if (IS_ERR(nfc->core_clk)) {
		dev_err(nfc->dev, "failed to get core clock\n");
		return PTR_ERR(nfc->core_clk);
	}

	nfc->device_clk = devm_clk_get(nfc->dev, "device");
	if (IS_ERR(nfc->device_clk)) {
		dev_err(nfc->dev, "failed to get device clock\n");
		return PTR_ERR(nfc->device_clk);
	}

	nfc->phase_tx = devm_clk_get(nfc->dev, "tx");
	if (IS_ERR(nfc->phase_tx)) {
		dev_err(nfc->dev, "failed to get TX clk\n");
		return PTR_ERR(nfc->phase_tx);
	}

	nfc->phase_rx = devm_clk_get(nfc->dev, "rx");
	if (IS_ERR(nfc->phase_rx)) {
		dev_err(nfc->dev, "failed to get RX clk\n");
		return PTR_ERR(nfc->phase_rx);
	}

	/* init SD_EMMC_CLOCK to sane defaults w/min clock rate */
	regmap_update_bits(nfc->reg_clk,
			   0, CLK_SELECT_NAND, CLK_SELECT_NAND);

	ret = clk_prepare_enable(nfc->core_clk);
	if (ret) {
		dev_err(nfc->dev, "failed to enable core clock\n");
		return ret;
	}

	ret = clk_prepare_enable(nfc->device_clk);
	if (ret) {
		dev_err(nfc->dev, "failed to enable device clock\n");
		goto err_device_clk;
	}

	ret = clk_prepare_enable(nfc->phase_tx);
	if (ret) {
		dev_err(nfc->dev, "failed to enable TX clock\n");
		goto err_phase_tx;
	}

	ret = clk_prepare_enable(nfc->phase_rx);
	if (ret) {
		dev_err(nfc->dev, "failed to enable RX clock\n");
		goto err_phase_rx;
	}

	ret = clk_set_rate(nfc->device_clk, 24000000);
	if (ret)
		goto err_phase_rx;

	return 0;
err_phase_rx:
	clk_disable_unprepare(nfc->phase_tx);
err_phase_tx:
	clk_disable_unprepare(nfc->device_clk);
err_device_clk:
	clk_disable_unprepare(nfc->core_clk);
	return ret;
}