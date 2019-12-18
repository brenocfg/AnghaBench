#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct ieee802154_hw {int flags; TYPE_3__* phy; scalar_t__ extra_tx_headroom; int /*<<< orphan*/ * parent; struct adf7242_local* priv; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct adf7242_local {struct ieee802154_hw* hw; int /*<<< orphan*/  bmux; int /*<<< orphan*/  wqueue; int /*<<< orphan*/  work; int /*<<< orphan*/  stat_msg; TYPE_4__ stat_xfer; int /*<<< orphan*/  buf_stat_tx; int /*<<< orphan*/  buf_stat_rx; int /*<<< orphan*/  tx_complete; struct spi_device* spi; } ;
struct TYPE_6__ {int* channels; int max_minbe; int min_maxbe; int max_maxbe; int max_frame_retries; int max_csma_backoffs; scalar_t__ min_csma_backoffs; scalar_t__ min_frame_retries; scalar_t__ min_minbe; void* tx_powers_size; void* tx_powers; void* cca_ed_levels_size; void* cca_ed_levels; int /*<<< orphan*/  cca_modes; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  perm_extended_addr; TYPE_2__ supported; TYPE_1__ cca; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_SPI_NOP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IEEE802154_HW_AFILT ; 
 int IEEE802154_HW_CSMA_PARAMS ; 
 int IEEE802154_HW_FRAME_RETRIES ; 
 int IEEE802154_HW_OMIT_CKSUM ; 
 int IEEE802154_HW_PROMISCUOUS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  NL802154_CCA_ENERGY ; 
 int WPAN_PHY_FLAG_CCA_ED_LEVEL ; 
 int WPAN_PHY_FLAG_CCA_MODE ; 
 int WPAN_PHY_FLAG_TXPOWER ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  adf7242_debugfs_init (struct adf7242_local*) ; 
 void* adf7242_ed_levels ; 
 int adf7242_hw_init (struct adf7242_local*) ; 
 int /*<<< orphan*/  adf7242_isr ; 
 int /*<<< orphan*/  adf7242_ops ; 
 void* adf7242_powers ; 
 int /*<<< orphan*/  adf7242_rx_cal_work ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct adf7242_local*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct adf7242_local*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct ieee802154_hw* ieee802154_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_free_hw (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  ieee802154_random_extended_addr (int /*<<< orphan*/ *) ; 
 int ieee802154_register_hw (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct adf7242_local*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int adf7242_probe(struct spi_device *spi)
{
	struct ieee802154_hw *hw;
	struct adf7242_local *lp;
	int ret, irq_type;

	if (!spi->irq) {
		dev_err(&spi->dev, "no IRQ specified\n");
		return -EINVAL;
	}

	hw = ieee802154_alloc_hw(sizeof(*lp), &adf7242_ops);
	if (!hw)
		return -ENOMEM;

	lp = hw->priv;
	lp->hw = hw;
	lp->spi = spi;

	hw->priv = lp;
	hw->parent = &spi->dev;
	hw->extra_tx_headroom = 0;

	/* We support only 2.4 Ghz */
	hw->phy->supported.channels[0] = 0x7FFF800;

	hw->flags = IEEE802154_HW_OMIT_CKSUM |
		    IEEE802154_HW_CSMA_PARAMS |
		    IEEE802154_HW_FRAME_RETRIES | IEEE802154_HW_AFILT |
		    IEEE802154_HW_PROMISCUOUS;

	hw->phy->flags = WPAN_PHY_FLAG_TXPOWER |
			 WPAN_PHY_FLAG_CCA_ED_LEVEL |
			 WPAN_PHY_FLAG_CCA_MODE;

	hw->phy->supported.cca_modes = BIT(NL802154_CCA_ENERGY);

	hw->phy->supported.cca_ed_levels = adf7242_ed_levels;
	hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(adf7242_ed_levels);

	hw->phy->cca.mode = NL802154_CCA_ENERGY;

	hw->phy->supported.tx_powers = adf7242_powers;
	hw->phy->supported.tx_powers_size = ARRAY_SIZE(adf7242_powers);

	hw->phy->supported.min_minbe = 0;
	hw->phy->supported.max_minbe = 8;

	hw->phy->supported.min_maxbe = 3;
	hw->phy->supported.max_maxbe = 8;

	hw->phy->supported.min_frame_retries = 0;
	hw->phy->supported.max_frame_retries = 15;

	hw->phy->supported.min_csma_backoffs = 0;
	hw->phy->supported.max_csma_backoffs = 5;

	ieee802154_random_extended_addr(&hw->phy->perm_extended_addr);

	mutex_init(&lp->bmux);
	init_completion(&lp->tx_complete);

	/* Setup Status Message */
	lp->stat_xfer.len = 1;
	lp->stat_xfer.tx_buf = &lp->buf_stat_tx;
	lp->stat_xfer.rx_buf = &lp->buf_stat_rx;
	lp->buf_stat_tx = CMD_SPI_NOP;

	spi_message_init(&lp->stat_msg);
	spi_message_add_tail(&lp->stat_xfer, &lp->stat_msg);

	spi_set_drvdata(spi, lp);
	INIT_DELAYED_WORK(&lp->work, adf7242_rx_cal_work);
	lp->wqueue = alloc_ordered_workqueue(dev_name(&spi->dev),
					     WQ_MEM_RECLAIM);
	if (unlikely(!lp->wqueue)) {
		ret = -ENOMEM;
		goto err_hw_init;
	}

	ret = adf7242_hw_init(lp);
	if (ret)
		goto err_hw_init;

	irq_type = irq_get_trigger_type(spi->irq);
	if (!irq_type)
		irq_type = IRQF_TRIGGER_HIGH;

	ret = devm_request_threaded_irq(&spi->dev, spi->irq, NULL, adf7242_isr,
					irq_type | IRQF_ONESHOT,
					dev_name(&spi->dev), lp);
	if (ret)
		goto err_hw_init;

	disable_irq(spi->irq);

	ret = ieee802154_register_hw(lp->hw);
	if (ret)
		goto err_hw_init;

	dev_set_drvdata(&spi->dev, lp);

	adf7242_debugfs_init(lp);

	dev_info(&spi->dev, "mac802154 IRQ-%d registered\n", spi->irq);

	return ret;

err_hw_init:
	mutex_destroy(&lp->bmux);
	ieee802154_free_hw(lp->hw);

	return ret;
}