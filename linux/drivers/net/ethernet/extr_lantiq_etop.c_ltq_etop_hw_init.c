#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ltq_etop_priv {TYPE_2__* pdev; struct ltq_etop_chan* ch; TYPE_1__* pldata; } ;
struct TYPE_7__ {int nr; scalar_t__ desc; int irq; int /*<<< orphan*/ * dev; } ;
struct ltq_etop_chan {int idx; TYPE_3__ dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int mii_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PORT_ETOP ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ETOP_MII_MASK ; 
 int /*<<< orphan*/  ETOP_MII_NORMAL ; 
 int /*<<< orphan*/  ETOP_MII_REVERSE ; 
 scalar_t__ IS_RX (int) ; 
 scalar_t__ IS_TX (int) ; 
 int /*<<< orphan*/  LQ_PPE32_ENET_MAC_CFG ; 
 scalar_t__ LTQ_DESC_NUM ; 
 int LTQ_DMA_CH0_INT ; 
 int /*<<< orphan*/  LTQ_ETOP_CFG ; 
 int MAX_DMA_CHAN ; 
#define  PHY_INTERFACE_MODE_MII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  PMU_PPE ; 
 int /*<<< orphan*/  PPE32_CGEN ; 
 int /*<<< orphan*/  ltq_dma_alloc_rx (TYPE_3__*) ; 
 int /*<<< orphan*/  ltq_dma_alloc_tx (TYPE_3__*) ; 
 int /*<<< orphan*/  ltq_dma_init_port (int /*<<< orphan*/ ) ; 
 scalar_t__ ltq_etop_alloc_skb (struct ltq_etop_chan*) ; 
 int /*<<< orphan*/  ltq_etop_dma_irq ; 
 int /*<<< orphan*/  ltq_etop_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_etop_w32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_pmu_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ltq_etop_priv*) ; 

__attribute__((used)) static int
ltq_etop_hw_init(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	int i;

	ltq_pmu_enable(PMU_PPE);

	switch (priv->pldata->mii_mode) {
	case PHY_INTERFACE_MODE_RMII:
		ltq_etop_w32_mask(ETOP_MII_MASK,
			ETOP_MII_REVERSE, LTQ_ETOP_CFG);
		break;

	case PHY_INTERFACE_MODE_MII:
		ltq_etop_w32_mask(ETOP_MII_MASK,
			ETOP_MII_NORMAL, LTQ_ETOP_CFG);
		break;

	default:
		netdev_err(dev, "unknown mii mode %d\n",
			priv->pldata->mii_mode);
		return -ENOTSUPP;
	}

	/* enable crc generation */
	ltq_etop_w32(PPE32_CGEN, LQ_PPE32_ENET_MAC_CFG);

	ltq_dma_init_port(DMA_PORT_ETOP);

	for (i = 0; i < MAX_DMA_CHAN; i++) {
		int irq = LTQ_DMA_CH0_INT + i;
		struct ltq_etop_chan *ch = &priv->ch[i];

		ch->idx = ch->dma.nr = i;
		ch->dma.dev = &priv->pdev->dev;

		if (IS_TX(i)) {
			ltq_dma_alloc_tx(&ch->dma);
			request_irq(irq, ltq_etop_dma_irq, 0, "etop_tx", priv);
		} else if (IS_RX(i)) {
			ltq_dma_alloc_rx(&ch->dma);
			for (ch->dma.desc = 0; ch->dma.desc < LTQ_DESC_NUM;
					ch->dma.desc++)
				if (ltq_etop_alloc_skb(ch))
					return -ENOMEM;
			ch->dma.desc = 0;
			request_irq(irq, ltq_etop_dma_irq, 0, "etop_rx", priv);
		}
		ch->dma.irq = irq;
	}
	return 0;
}