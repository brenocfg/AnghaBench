#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct smsc9420_pdata {int software_irq_signal; int /*<<< orphan*/  int_lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CFG ; 
 int BUS_CFG_RXTXWEIGHT_4_1 ; 
 int /*<<< orphan*/  BUS_MODE ; 
 int BUS_MODE_DBO_ ; 
 int BUS_MODE_DMA_BURST_LENGTH_16 ; 
 int /*<<< orphan*/  DMAC_CONTROL ; 
 int DMAC_CONTROL_OSF_ ; 
 int DMAC_CONTROL_SF_ ; 
 int DMAC_CONTROL_SR_ ; 
 int DMAC_CONTROL_ST_ ; 
 int /*<<< orphan*/  DMAC_INTR_ENA ; 
 int DMAC_INTR_ENA_NIS_ ; 
 int DMAC_INTR_ENA_RX_ ; 
 int DMAC_INTR_ENA_TX_ ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EADDRNOTAVAIL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIO_CFG ; 
 int GPIO_CFG_LED_1_ ; 
 int GPIO_CFG_LED_2_ ; 
 int GPIO_CFG_LED_3_ ; 
 int /*<<< orphan*/  INT_CFG ; 
 int INT_CFG_INT_DEAS_MASK ; 
 int INT_CFG_IRQ_EN_ ; 
 int /*<<< orphan*/  INT_CTL ; 
 int INT_CTL_SW_INT_EN_ ; 
 int INT_DEAS_TIME ; 
 int /*<<< orphan*/  INT_STAT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_RXEN_ ; 
 int MAC_CR_TXEN_ ; 
 int /*<<< orphan*/  RX_POLL_DEMAND ; 
 int /*<<< orphan*/  free_irq (int const,struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int request_irq (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smsc9420_pdata*) ; 
 int smsc9420_alloc_rx_ring (struct smsc9420_pdata*) ; 
 int smsc9420_alloc_tx_ring (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_dmac_soft_reset (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_free_rx_ring (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_free_tx_ring (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_isr ; 
 int smsc9420_mii_init (struct net_device*) ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc9420_set_mac_address (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smsc9420_open(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	u32 bus_mode, mac_cr, dmac_control, int_cfg, dma_intr_ena, int_ctl;
	const int irq = pd->pdev->irq;
	unsigned long flags;
	int result = 0, timeout;

	if (!is_valid_ether_addr(dev->dev_addr)) {
		netif_warn(pd, ifup, pd->dev,
			   "dev_addr is not a valid MAC address\n");
		result = -EADDRNOTAVAIL;
		goto out_0;
	}

	netif_carrier_off(dev);

	/* disable, mask and acknowledge all interrupts */
	spin_lock_irqsave(&pd->int_lock, flags);
	int_cfg = smsc9420_reg_read(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_write(pd, INT_CFG, int_cfg);
	smsc9420_reg_write(pd, INT_CTL, 0);
	spin_unlock_irqrestore(&pd->int_lock, flags);
	smsc9420_reg_write(pd, DMAC_INTR_ENA, 0);
	smsc9420_reg_write(pd, INT_STAT, 0xFFFFFFFF);
	smsc9420_pci_flush_write(pd);

	result = request_irq(irq, smsc9420_isr, IRQF_SHARED, DRV_NAME, pd);
	if (result) {
		netif_warn(pd, ifup, pd->dev, "Unable to use IRQ = %d\n", irq);
		result = -ENODEV;
		goto out_0;
	}

	smsc9420_dmac_soft_reset(pd);

	/* make sure MAC_CR is sane */
	smsc9420_reg_write(pd, MAC_CR, 0);

	smsc9420_set_mac_address(dev);

	/* Configure GPIO pins to drive LEDs */
	smsc9420_reg_write(pd, GPIO_CFG,
		(GPIO_CFG_LED_3_ | GPIO_CFG_LED_2_ | GPIO_CFG_LED_1_));

	bus_mode = BUS_MODE_DMA_BURST_LENGTH_16;

#ifdef __BIG_ENDIAN
	bus_mode |= BUS_MODE_DBO_;
#endif

	smsc9420_reg_write(pd, BUS_MODE, bus_mode);

	smsc9420_pci_flush_write(pd);

	/* set bus master bridge arbitration priority for Rx and TX DMA */
	smsc9420_reg_write(pd, BUS_CFG, BUS_CFG_RXTXWEIGHT_4_1);

	smsc9420_reg_write(pd, DMAC_CONTROL,
		(DMAC_CONTROL_SF_ | DMAC_CONTROL_OSF_));

	smsc9420_pci_flush_write(pd);

	/* test the IRQ connection to the ISR */
	netif_dbg(pd, ifup, pd->dev, "Testing ISR using IRQ %d\n", irq);
	pd->software_irq_signal = false;

	spin_lock_irqsave(&pd->int_lock, flags);
	/* configure interrupt deassertion timer and enable interrupts */
	int_cfg = smsc9420_reg_read(pd, INT_CFG) | INT_CFG_IRQ_EN_;
	int_cfg &= ~(INT_CFG_INT_DEAS_MASK);
	int_cfg |= (INT_DEAS_TIME & INT_CFG_INT_DEAS_MASK);
	smsc9420_reg_write(pd, INT_CFG, int_cfg);

	/* unmask software interrupt */
	int_ctl = smsc9420_reg_read(pd, INT_CTL) | INT_CTL_SW_INT_EN_;
	smsc9420_reg_write(pd, INT_CTL, int_ctl);
	spin_unlock_irqrestore(&pd->int_lock, flags);
	smsc9420_pci_flush_write(pd);

	timeout = 1000;
	while (timeout--) {
		if (pd->software_irq_signal)
			break;
		msleep(1);
	}

	/* disable interrupts */
	spin_lock_irqsave(&pd->int_lock, flags);
	int_cfg = smsc9420_reg_read(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_write(pd, INT_CFG, int_cfg);
	spin_unlock_irqrestore(&pd->int_lock, flags);

	if (!pd->software_irq_signal) {
		netif_warn(pd, ifup, pd->dev, "ISR failed signaling test\n");
		result = -ENODEV;
		goto out_free_irq_1;
	}

	netif_dbg(pd, ifup, pd->dev, "ISR passed test using IRQ %d\n", irq);

	result = smsc9420_alloc_tx_ring(pd);
	if (result) {
		netif_warn(pd, ifup, pd->dev,
			   "Failed to Initialize tx dma ring\n");
		result = -ENOMEM;
		goto out_free_irq_1;
	}

	result = smsc9420_alloc_rx_ring(pd);
	if (result) {
		netif_warn(pd, ifup, pd->dev,
			   "Failed to Initialize rx dma ring\n");
		result = -ENOMEM;
		goto out_free_tx_ring_2;
	}

	result = smsc9420_mii_init(dev);
	if (result) {
		netif_warn(pd, ifup, pd->dev, "Failed to initialize Phy\n");
		result = -ENODEV;
		goto out_free_rx_ring_3;
	}

	/* Bring the PHY up */
	phy_start(dev->phydev);

	napi_enable(&pd->napi);

	/* start tx and rx */
	mac_cr = smsc9420_reg_read(pd, MAC_CR) | MAC_CR_TXEN_ | MAC_CR_RXEN_;
	smsc9420_reg_write(pd, MAC_CR, mac_cr);

	dmac_control = smsc9420_reg_read(pd, DMAC_CONTROL);
	dmac_control |= DMAC_CONTROL_ST_ | DMAC_CONTROL_SR_;
	smsc9420_reg_write(pd, DMAC_CONTROL, dmac_control);
	smsc9420_pci_flush_write(pd);

	dma_intr_ena = smsc9420_reg_read(pd, DMAC_INTR_ENA);
	dma_intr_ena |=
		(DMAC_INTR_ENA_TX_ | DMAC_INTR_ENA_RX_ | DMAC_INTR_ENA_NIS_);
	smsc9420_reg_write(pd, DMAC_INTR_ENA, dma_intr_ena);
	smsc9420_pci_flush_write(pd);

	netif_wake_queue(dev);

	smsc9420_reg_write(pd, RX_POLL_DEMAND, 1);

	/* enable interrupts */
	spin_lock_irqsave(&pd->int_lock, flags);
	int_cfg = smsc9420_reg_read(pd, INT_CFG) | INT_CFG_IRQ_EN_;
	smsc9420_reg_write(pd, INT_CFG, int_cfg);
	spin_unlock_irqrestore(&pd->int_lock, flags);

	return 0;

out_free_rx_ring_3:
	smsc9420_free_rx_ring(pd);
out_free_tx_ring_2:
	smsc9420_free_tx_ring(pd);
out_free_irq_1:
	free_irq(irq, pd);
out_0:
	return result;
}