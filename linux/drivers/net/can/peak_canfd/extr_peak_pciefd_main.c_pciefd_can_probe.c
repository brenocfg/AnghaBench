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
typedef  int u32 ;
struct TYPE_5__ {int freq; } ;
struct TYPE_6__ {TYPE_1__ clock; } ;
struct TYPE_7__ {int cmd_maxlen; TYPE_2__ can; int /*<<< orphan*/  index; int /*<<< orphan*/ * cmd_buffer; int /*<<< orphan*/  write_tx_msg; int /*<<< orphan*/  alloc_tx_msg; int /*<<< orphan*/  enable_tx_path; int /*<<< orphan*/  post_cmd; int /*<<< orphan*/  write_cmd; int /*<<< orphan*/  pre_cmd; } ;
struct pciefd_can {scalar_t__ reg_base; int /*<<< orphan*/  tx_lock; TYPE_3__ ucan; void* tx_dma_vaddr; int /*<<< orphan*/  tx_dma_laddr; void* rx_dma_vaddr; int /*<<< orphan*/  rx_dma_laddr; struct pciefd_board* board; int /*<<< orphan*/  pucan_cmd; } ;
struct pciefd_board {size_t can_count; TYPE_4__* pci_dev; struct pciefd_can** can; scalar_t__ reg_base; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
#define  CANFD_CLK_SEL_20MHZ 133 
#define  CANFD_CLK_SEL_24MHZ 132 
#define  CANFD_CLK_SEL_30MHZ 131 
#define  CANFD_CLK_SEL_40MHZ 130 
#define  CANFD_CLK_SEL_60MHZ 129 
#define  CANFD_CLK_SEL_80MHZ 128 
 int CANFD_MISC_TS_RST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PCIEFD_CANX_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIEFD_ECHO_SKB_MAX ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_CLK_SEL ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_MISC ; 
 int PCIEFD_RX_DMA_SIZE ; 
 int PCIEFD_TX_DMA_SIZE ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_peak_canfd_dev (int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 void* dmam_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 struct pciefd_can* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pciefd_alloc_tx_msg ; 
 int pciefd_can_readreg (struct pciefd_can*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_enable_tx_path ; 
 int /*<<< orphan*/  pciefd_post_cmd ; 
 int /*<<< orphan*/  pciefd_pre_cmd ; 
 int /*<<< orphan*/  pciefd_write_cmd ; 
 int /*<<< orphan*/  pciefd_write_tx_msg ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pciefd_can_probe(struct pciefd_board *pciefd)
{
	struct net_device *ndev;
	struct pciefd_can *priv;
	u32 clk;
	int err;

	/* allocate the candev object with default isize of echo skbs ring */
	ndev = alloc_peak_canfd_dev(sizeof(*priv), pciefd->can_count,
				    PCIEFD_ECHO_SKB_MAX);
	if (!ndev) {
		dev_err(&pciefd->pci_dev->dev,
			"failed to alloc candev object\n");
		goto failure;
	}

	priv = netdev_priv(ndev);

	/* fill-in candev private object: */

	/* setup PCIe-FD own callbacks */
	priv->ucan.pre_cmd = pciefd_pre_cmd;
	priv->ucan.write_cmd = pciefd_write_cmd;
	priv->ucan.post_cmd = pciefd_post_cmd;
	priv->ucan.enable_tx_path = pciefd_enable_tx_path;
	priv->ucan.alloc_tx_msg = pciefd_alloc_tx_msg;
	priv->ucan.write_tx_msg = pciefd_write_tx_msg;

	/* setup PCIe-FD own command buffer */
	priv->ucan.cmd_buffer = &priv->pucan_cmd;
	priv->ucan.cmd_maxlen = sizeof(priv->pucan_cmd);

	priv->board = pciefd;

	/* CAN config regs block address */
	priv->reg_base = pciefd->reg_base + PCIEFD_CANX_OFF(priv->ucan.index);

	/* allocate non-cacheable DMA'able 4KB memory area for Rx */
	priv->rx_dma_vaddr = dmam_alloc_coherent(&pciefd->pci_dev->dev,
						 PCIEFD_RX_DMA_SIZE,
						 &priv->rx_dma_laddr,
						 GFP_KERNEL);
	if (!priv->rx_dma_vaddr) {
		dev_err(&pciefd->pci_dev->dev,
			"Rx dmam_alloc_coherent(%u) failure\n",
			PCIEFD_RX_DMA_SIZE);
		goto err_free_candev;
	}

	/* allocate non-cacheable DMA'able 4KB memory area for Tx */
	priv->tx_dma_vaddr = dmam_alloc_coherent(&pciefd->pci_dev->dev,
						 PCIEFD_TX_DMA_SIZE,
						 &priv->tx_dma_laddr,
						 GFP_KERNEL);
	if (!priv->tx_dma_vaddr) {
		dev_err(&pciefd->pci_dev->dev,
			"Tx dmam_alloc_coherent(%u) failure\n",
			PCIEFD_TX_DMA_SIZE);
		goto err_free_candev;
	}

	/* CAN clock in RST mode */
	pciefd_can_writereg(priv, CANFD_MISC_TS_RST, PCIEFD_REG_CAN_MISC);

	/* read current clock value */
	clk = pciefd_can_readreg(priv, PCIEFD_REG_CAN_CLK_SEL);
	switch (clk) {
	case CANFD_CLK_SEL_20MHZ:
		priv->ucan.can.clock.freq = 20 * 1000 * 1000;
		break;
	case CANFD_CLK_SEL_24MHZ:
		priv->ucan.can.clock.freq = 24 * 1000 * 1000;
		break;
	case CANFD_CLK_SEL_30MHZ:
		priv->ucan.can.clock.freq = 30 * 1000 * 1000;
		break;
	case CANFD_CLK_SEL_40MHZ:
		priv->ucan.can.clock.freq = 40 * 1000 * 1000;
		break;
	case CANFD_CLK_SEL_60MHZ:
		priv->ucan.can.clock.freq = 60 * 1000 * 1000;
		break;
	default:
		pciefd_can_writereg(priv, CANFD_CLK_SEL_80MHZ,
				    PCIEFD_REG_CAN_CLK_SEL);

		/* fall through */
	case CANFD_CLK_SEL_80MHZ:
		priv->ucan.can.clock.freq = 80 * 1000 * 1000;
		break;
	}

	ndev->irq = pciefd->pci_dev->irq;

	SET_NETDEV_DEV(ndev, &pciefd->pci_dev->dev);

	err = register_candev(ndev);
	if (err) {
		dev_err(&pciefd->pci_dev->dev,
			"couldn't register CAN device: %d\n", err);
		goto err_free_candev;
	}

	spin_lock_init(&priv->tx_lock);

	/* save the object address in the board structure */
	pciefd->can[pciefd->can_count] = priv;

	dev_info(&pciefd->pci_dev->dev, "%s at reg_base=0x%p irq=%d\n",
		 ndev->name, priv->reg_base, ndev->irq);

	return 0;

err_free_candev:
	free_candev(ndev);

failure:
	return -ENOMEM;
}