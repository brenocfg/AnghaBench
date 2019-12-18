#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_13__ {int /*<<< orphan*/  start_signal_voltage_switch; int /*<<< orphan*/  card_busy; } ;
struct tmio_mmc_host {int bus_shift; int (* clk_enable ) (struct tmio_mmc_host*) ;TYPE_4__* mmc; int /*<<< orphan*/  hs400_complete; int /*<<< orphan*/  hs400_downgrade; int /*<<< orphan*/  prepare_hs400_tuning; int /*<<< orphan*/  check_scc_error; int /*<<< orphan*/  select_tuning; int /*<<< orphan*/  prepare_tuning; int /*<<< orphan*/  init_tuning; TYPE_2__* pdev; int /*<<< orphan*/  hw_reset; scalar_t__ ctl; int /*<<< orphan*/  sdcard_irq_setbit_mask; TYPE_1__ ops; struct tmio_mmc_dma_ops const* dma_ops; int /*<<< orphan*/  multi_io_quirk; int /*<<< orphan*/  set_clock; int /*<<< orphan*/  (* clk_disable ) (struct tmio_mmc_host*) ;int /*<<< orphan*/  write16_hook; } ;
struct tmio_mmc_dma_ops {int dummy; } ;
struct tmio_mmc_dma {int /*<<< orphan*/  enable; int /*<<< orphan*/  filter; int /*<<< orphan*/  dma_buswidth; } ;
struct tmio_mmc_data {int flags; scalar_t__ max_blk_count; int alignment_shift; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  capabilities2; int /*<<< orphan*/  max_segs; int /*<<< orphan*/  dma_rx_offset; int /*<<< orphan*/  ocr_mask; } ;
struct soc_device_attribute {struct renesas_sdhi_quirks* data; } ;
struct resource {scalar_t__ start; } ;
struct renesas_sdhi_scc {scalar_t__ clk_rate; int /*<<< orphan*/  tap_hs400; int /*<<< orphan*/  tap; } ;
struct renesas_sdhi_quirks {scalar_t__ hs400_4taps; scalar_t__ hs400_disabled; } ;
struct renesas_sdhi_of_data {int tmio_flags; scalar_t__ max_blk_count; int bus_shift; int taps_num; struct renesas_sdhi_scc* taps; scalar_t__ scc_offset; int /*<<< orphan*/  dma_buswidth; int /*<<< orphan*/  max_segs; int /*<<< orphan*/  dma_rx_offset; int /*<<< orphan*/  capabilities2; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  tmio_ocr_mask; } ;
struct renesas_sdhi {int /*<<< orphan*/  scc_tappos_hs400; int /*<<< orphan*/  scc_tappos; scalar_t__ scc_ctl; struct tmio_mmc_host* pinctrl; void* pins_uhs; void* pins_default; struct tmio_mmc_host* clk_cd; struct tmio_mmc_host* clk; struct tmio_mmc_dma dma_priv; struct tmio_mmc_data mmc_data; } ;
struct TYPE_15__ {struct tmio_mmc_data* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_16__ {int caps2; int caps; scalar_t__ f_max; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_VERSION ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct tmio_mmc_host*) ; 
 int MMC_CAP2_HS200_1_8V_SDR ; 
 int MMC_CAP2_HS400 ; 
 int MMC_CAP2_HS400_1_8V ; 
 int MMC_CAP2_HS400_ES ; 
 int /*<<< orphan*/  MMC_CAP2_NO_WRITE_PROTECT ; 
 int MMC_CAP_HW_RESET ; 
 int /*<<< orphan*/  MMC_CAP_MMC_HIGHSPEED ; 
 int MMC_CAP_UHS_SDR104 ; 
 char* PINCTRL_STATE_DEFAULT ; 
 int PTR_ERR (struct tmio_mmc_host*) ; 
 scalar_t__ SDHI_VER_GEN2_SDR104 ; 
 scalar_t__ SDHI_VER_GEN2_SDR50 ; 
 int TMIO_MMC_BLKSZ_2BYTES ; 
 int TMIO_MMC_HAVE_4TAP_HS400 ; 
 int TMIO_MMC_HAVE_CBSY ; 
 int TMIO_MMC_HAVE_CMD12_CTRL ; 
 int TMIO_MMC_MIN_RCAR2 ; 
 int TMIO_MMC_SDIO_IRQ ; 
 int TMIO_MMC_SDIO_STATUS_SETBITS ; 
 int /*<<< orphan*/  TMIO_STAT_ALWAYS_SET_27 ; 
 scalar_t__ U16_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 struct renesas_sdhi* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct tmio_mmc_host* devm_pinctrl_get (TYPE_3__*) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmio_mmc_host*) ; 
 scalar_t__ mmc_can_gpio_ro (TYPE_4__*) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_4__*) ; 
 struct renesas_sdhi_of_data* of_device_get_match_data (TYPE_3__*) ; 
 void* pinctrl_lookup_state (struct tmio_mmc_host*,char*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  renesas_sdhi_card_busy ; 
 int /*<<< orphan*/  renesas_sdhi_check_scc_error ; 
 int /*<<< orphan*/  renesas_sdhi_clk_disable (struct tmio_mmc_host*) ; 
 int renesas_sdhi_clk_enable (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  renesas_sdhi_disable_scc ; 
 int /*<<< orphan*/  renesas_sdhi_enable_dma ; 
 int /*<<< orphan*/  renesas_sdhi_hs400_complete ; 
 int /*<<< orphan*/  renesas_sdhi_hw_reset ; 
 int /*<<< orphan*/  renesas_sdhi_init_tuning ; 
 int /*<<< orphan*/  renesas_sdhi_multi_io_quirk ; 
 int /*<<< orphan*/  renesas_sdhi_prepare_hs400_tuning ; 
 int /*<<< orphan*/  renesas_sdhi_prepare_tuning ; 
 int /*<<< orphan*/  renesas_sdhi_select_tuning ; 
 int /*<<< orphan*/  renesas_sdhi_set_clock ; 
 int /*<<< orphan*/  renesas_sdhi_start_signal_voltage_switch ; 
 int /*<<< orphan*/  renesas_sdhi_write16_hook ; 
 int resource_size (struct resource*) ; 
 scalar_t__ sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhi_quirks_match ; 
 int /*<<< orphan*/  shdma_chan_filter ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 struct tmio_mmc_host* tmio_mmc_host_alloc (struct platform_device*,struct tmio_mmc_data*) ; 
 int /*<<< orphan*/  tmio_mmc_host_free (struct tmio_mmc_host*) ; 
 int tmio_mmc_host_probe (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_host_remove (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_irq ; 

int renesas_sdhi_probe(struct platform_device *pdev,
		       const struct tmio_mmc_dma_ops *dma_ops)
{
	struct tmio_mmc_data *mmd = pdev->dev.platform_data;
	const struct renesas_sdhi_quirks *quirks = NULL;
	const struct renesas_sdhi_of_data *of_data;
	const struct soc_device_attribute *attr;
	struct tmio_mmc_data *mmc_data;
	struct tmio_mmc_dma *dma_priv;
	struct tmio_mmc_host *host;
	struct renesas_sdhi *priv;
	int num_irqs, irq, ret, i;
	struct resource *res;
	u16 ver;

	of_data = of_device_get_match_data(&pdev->dev);

	attr = soc_device_match(sdhi_quirks_match);
	if (attr)
		quirks = attr->data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct renesas_sdhi),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mmc_data = &priv->mmc_data;
	dma_priv = &priv->dma_priv;

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		dev_err(&pdev->dev, "cannot get clock: %d\n", ret);
		return ret;
	}

	/*
	 * Some controllers provide a 2nd clock just to run the internal card
	 * detection logic. Unfortunately, the existing driver architecture does
	 * not support a separation of clocks for runtime PM usage. When
	 * native hotplug is used, the tmio driver assumes that the core
	 * must continue to run for card detect to stay active, so we cannot
	 * disable it.
	 * Additionally, it is prohibited to supply a clock to the core but not
	 * to the card detect circuit. That leaves us with if separate clocks
	 * are presented, we must treat them both as virtually 1 clock.
	 */
	priv->clk_cd = devm_clk_get(&pdev->dev, "cd");
	if (IS_ERR(priv->clk_cd))
		priv->clk_cd = NULL;

	priv->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (!IS_ERR(priv->pinctrl)) {
		priv->pins_default = pinctrl_lookup_state(priv->pinctrl,
						PINCTRL_STATE_DEFAULT);
		priv->pins_uhs = pinctrl_lookup_state(priv->pinctrl,
						"state_uhs");
	}

	host = tmio_mmc_host_alloc(pdev, mmc_data);
	if (IS_ERR(host))
		return PTR_ERR(host);

	if (of_data) {
		mmc_data->flags |= of_data->tmio_flags;
		mmc_data->ocr_mask = of_data->tmio_ocr_mask;
		mmc_data->capabilities |= of_data->capabilities;
		mmc_data->capabilities2 |= of_data->capabilities2;
		mmc_data->dma_rx_offset = of_data->dma_rx_offset;
		mmc_data->max_blk_count = of_data->max_blk_count;
		mmc_data->max_segs = of_data->max_segs;
		dma_priv->dma_buswidth = of_data->dma_buswidth;
		host->bus_shift = of_data->bus_shift;
	}

	host->write16_hook	= renesas_sdhi_write16_hook;
	host->clk_enable	= renesas_sdhi_clk_enable;
	host->clk_disable	= renesas_sdhi_clk_disable;
	host->set_clock		= renesas_sdhi_set_clock;
	host->multi_io_quirk	= renesas_sdhi_multi_io_quirk;
	host->dma_ops		= dma_ops;

	if (quirks && quirks->hs400_disabled)
		host->mmc->caps2 &= ~(MMC_CAP2_HS400 | MMC_CAP2_HS400_ES);

	if (quirks && quirks->hs400_4taps)
		mmc_data->flags |= TMIO_MMC_HAVE_4TAP_HS400;

	/* For some SoC, we disable internal WP. GPIO may override this */
	if (mmc_can_gpio_ro(host->mmc))
		mmc_data->capabilities2 &= ~MMC_CAP2_NO_WRITE_PROTECT;

	/* SDR speeds are only available on Gen2+ */
	if (mmc_data->flags & TMIO_MMC_MIN_RCAR2) {
		/* card_busy caused issues on r8a73a4 (pre-Gen2) CD-less SDHI */
		host->ops.card_busy = renesas_sdhi_card_busy;
		host->ops.start_signal_voltage_switch =
			renesas_sdhi_start_signal_voltage_switch;
		host->sdcard_irq_setbit_mask = TMIO_STAT_ALWAYS_SET_27;

		/* SDR and HS200/400 registers requires HW reset */
		if (of_data && of_data->scc_offset) {
			priv->scc_ctl = host->ctl + of_data->scc_offset;
			host->mmc->caps |= MMC_CAP_HW_RESET;
			host->hw_reset = renesas_sdhi_hw_reset;
		}
	}

	/* Orginally registers were 16 bit apart, could be 32 or 64 nowadays */
	if (!host->bus_shift && resource_size(res) > 0x100) /* old way to determine the shift */
		host->bus_shift = 1;

	if (mmd)
		*mmc_data = *mmd;

	dma_priv->filter = shdma_chan_filter;
	dma_priv->enable = renesas_sdhi_enable_dma;

	mmc_data->alignment_shift = 1; /* 2-byte alignment */
	mmc_data->capabilities |= MMC_CAP_MMC_HIGHSPEED;

	/*
	 * All SDHI blocks support 2-byte and larger block sizes in 4-bit
	 * bus width mode.
	 */
	mmc_data->flags |= TMIO_MMC_BLKSZ_2BYTES;

	/*
	 * All SDHI blocks support SDIO IRQ signalling.
	 */
	mmc_data->flags |= TMIO_MMC_SDIO_IRQ;

	/* All SDHI have CMD12 control bit */
	mmc_data->flags |= TMIO_MMC_HAVE_CMD12_CTRL;

	/* All SDHI have SDIO status bits which must be 1 */
	mmc_data->flags |= TMIO_MMC_SDIO_STATUS_SETBITS;

	ret = renesas_sdhi_clk_enable(host);
	if (ret)
		goto efree;

	ver = sd_ctrl_read16(host, CTL_VERSION);
	/* GEN2_SDR104 is first known SDHI to use 32bit block count */
	if (ver < SDHI_VER_GEN2_SDR104 && mmc_data->max_blk_count > U16_MAX)
		mmc_data->max_blk_count = U16_MAX;

	/* One Gen2 SDHI incarnation does NOT have a CBSY bit */
	if (ver == SDHI_VER_GEN2_SDR50)
		mmc_data->flags &= ~TMIO_MMC_HAVE_CBSY;

	ret = tmio_mmc_host_probe(host);
	if (ret < 0)
		goto edisclk;

	/* Enable tuning iff we have an SCC and a supported mode */
	if (of_data && of_data->scc_offset &&
	    (host->mmc->caps & MMC_CAP_UHS_SDR104 ||
	     host->mmc->caps2 & (MMC_CAP2_HS200_1_8V_SDR |
				 MMC_CAP2_HS400_1_8V))) {
		const struct renesas_sdhi_scc *taps = of_data->taps;
		bool hit = false;

		for (i = 0; i < of_data->taps_num; i++) {
			if (taps[i].clk_rate == 0 ||
			    taps[i].clk_rate == host->mmc->f_max) {
				priv->scc_tappos = taps->tap;
				priv->scc_tappos_hs400 = taps->tap_hs400;
				hit = true;
				break;
			}
		}

		if (!hit)
			dev_warn(&host->pdev->dev, "Unknown clock rate for SDR104\n");

		host->init_tuning = renesas_sdhi_init_tuning;
		host->prepare_tuning = renesas_sdhi_prepare_tuning;
		host->select_tuning = renesas_sdhi_select_tuning;
		host->check_scc_error = renesas_sdhi_check_scc_error;
		host->prepare_hs400_tuning =
			renesas_sdhi_prepare_hs400_tuning;
		host->hs400_downgrade = renesas_sdhi_disable_scc;
		host->hs400_complete = renesas_sdhi_hs400_complete;
	}

	num_irqs = platform_irq_count(pdev);
	if (num_irqs < 0) {
		ret = num_irqs;
		goto eirq;
	}

	/* There must be at least one IRQ source */
	if (!num_irqs) {
		ret = -ENXIO;
		goto eirq;
	}

	for (i = 0; i < num_irqs; i++) {
		irq = platform_get_irq(pdev, i);
		if (irq < 0) {
			ret = irq;
			goto eirq;
		}

		ret = devm_request_irq(&pdev->dev, irq, tmio_mmc_irq, 0,
				       dev_name(&pdev->dev), host);
		if (ret)
			goto eirq;
	}

	dev_info(&pdev->dev, "%s base at 0x%08lx max clock rate %u MHz\n",
		 mmc_hostname(host->mmc), (unsigned long)
		 (platform_get_resource(pdev, IORESOURCE_MEM, 0)->start),
		 host->mmc->f_max / 1000000);

	return ret;

eirq:
	tmio_mmc_host_remove(host);
edisclk:
	renesas_sdhi_clk_disable(host);
efree:
	tmio_mmc_host_free(host);

	return ret;
}