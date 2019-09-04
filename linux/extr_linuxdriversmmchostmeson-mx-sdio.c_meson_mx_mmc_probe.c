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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;
struct meson_mx_mmc_host {struct platform_device* core_clk; struct platform_device* cfg_div_clk; struct platform_device* base; int /*<<< orphan*/ * controller_dev; struct platform_device* parent_clk; int /*<<< orphan*/  cmd_timeout; int /*<<< orphan*/  irq_lock; struct mmc_host* mmc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int MESON_MX_SDIO_CONF ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_CMD_ARGUMENT_BITS_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_M_ENDIAN_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_WRITE_CRC_OK_STATUS_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_WRITE_NWR_MASK ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct platform_device*) ; 
 int clk_prepare_enable (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct platform_device* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct meson_mx_mmc_host*) ; 
 int meson_mx_mmc_add_host (struct meson_mx_mmc_host*) ; 
 int /*<<< orphan*/  meson_mx_mmc_irq ; 
 int /*<<< orphan*/  meson_mx_mmc_irq_thread ; 
 int meson_mx_mmc_register_clks (struct meson_mx_mmc_host*) ; 
 struct platform_device* meson_mx_mmc_slot_pdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meson_mx_mmc_soft_reset (struct meson_mx_mmc_host*) ; 
 int /*<<< orphan*/  meson_mx_mmc_timeout ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct meson_mx_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  of_platform_device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_mx_mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,struct platform_device*) ; 

__attribute__((used)) static int meson_mx_mmc_probe(struct platform_device *pdev)
{
	struct platform_device *slot_pdev;
	struct mmc_host *mmc;
	struct meson_mx_mmc_host *host;
	struct resource *res;
	int ret, irq;
	u32 conf;

	slot_pdev = meson_mx_mmc_slot_pdev(&pdev->dev);
	if (!slot_pdev)
		return -ENODEV;
	else if (IS_ERR(slot_pdev))
		return PTR_ERR(slot_pdev);

	mmc = mmc_alloc_host(sizeof(*host), &slot_pdev->dev);
	if (!mmc) {
		ret = -ENOMEM;
		goto error_unregister_slot_pdev;
	}

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->controller_dev = &pdev->dev;

	spin_lock_init(&host->irq_lock);
	timer_setup(&host->cmd_timeout, meson_mx_mmc_timeout, 0);

	platform_set_drvdata(pdev, host);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->base = devm_ioremap_resource(host->controller_dev, res);
	if (IS_ERR(host->base)) {
		ret = PTR_ERR(host->base);
		goto error_free_mmc;
	}

	irq = platform_get_irq(pdev, 0);
	ret = devm_request_threaded_irq(host->controller_dev, irq,
					meson_mx_mmc_irq,
					meson_mx_mmc_irq_thread, IRQF_ONESHOT,
					NULL, host);
	if (ret)
		goto error_free_mmc;

	host->core_clk = devm_clk_get(host->controller_dev, "core");
	if (IS_ERR(host->core_clk)) {
		ret = PTR_ERR(host->core_clk);
		goto error_free_mmc;
	}

	host->parent_clk = devm_clk_get(host->controller_dev, "clkin");
	if (IS_ERR(host->parent_clk)) {
		ret = PTR_ERR(host->parent_clk);
		goto error_free_mmc;
	}

	ret = meson_mx_mmc_register_clks(host);
	if (ret)
		goto error_free_mmc;

	ret = clk_prepare_enable(host->core_clk);
	if (ret) {
		dev_err(host->controller_dev, "Failed to enable core clock\n");
		goto error_free_mmc;
	}

	ret = clk_prepare_enable(host->cfg_div_clk);
	if (ret) {
		dev_err(host->controller_dev, "Failed to enable MMC clock\n");
		goto error_disable_core_clk;
	}

	conf = 0;
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_CMD_ARGUMENT_BITS_MASK, 39);
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_M_ENDIAN_MASK, 0x3);
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_WRITE_NWR_MASK, 0x2);
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_WRITE_CRC_OK_STATUS_MASK, 0x2);
	writel(conf, host->base + MESON_MX_SDIO_CONF);

	meson_mx_mmc_soft_reset(host);

	ret = meson_mx_mmc_add_host(host);
	if (ret)
		goto error_disable_clks;

	return 0;

error_disable_clks:
	clk_disable_unprepare(host->cfg_div_clk);
error_disable_core_clk:
	clk_disable_unprepare(host->core_clk);
error_free_mmc:
	mmc_free_host(mmc);
error_unregister_slot_pdev:
	of_platform_device_destroy(&slot_pdev->dev, NULL);
	return ret;
}