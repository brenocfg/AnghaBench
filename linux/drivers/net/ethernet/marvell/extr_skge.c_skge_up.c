#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct skge_tx_desc {int dummy; } ;
struct skge_rx_desc {int dummy; } ;
struct TYPE_4__ {int count; scalar_t__ to_clean; scalar_t__ to_use; int /*<<< orphan*/  start; } ;
struct skge_port {int port; scalar_t__ rx_buf_size; size_t mem_size; int dma; int /*<<< orphan*/ * mem; TYPE_1__ rx_ring; TYPE_1__ tx_ring; int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; struct skge_hw* hw; } ;
struct skge_hw {int ports; int ram_size; int ram_offset; TYPE_2__* pdev; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  intr_mask; int /*<<< orphan*/  phy_lock; } ;
struct net_device {scalar_t__ mtu; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CSR_IRQ_CL_F ; 
 int CSR_START ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  LED_MODE_ON ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 scalar_t__ RX_BUF_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  genesis_mac_init (struct skge_hw*,int) ; 
 int /*<<< orphan*/  ifup ; 
 scalar_t__ is_genesis (struct skge_hw*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (TYPE_2__*,size_t,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (TYPE_2__*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * portmask ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skge_hw*) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  skge_intr ; 
 int /*<<< orphan*/  skge_led (struct skge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_qset (struct skge_port*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skge_ramset (struct skge_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int skge_ring_alloc (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  skge_rx_clean (struct skge_port*) ; 
 int skge_rx_fill (struct net_device*) ; 
 int /*<<< orphan*/  skge_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * txqaddr ; 
 scalar_t__ upper_32_bits (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  yukon_mac_init (struct skge_hw*,int) ; 

__attribute__((used)) static int skge_up(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u32 chunk, ram_addr;
	size_t rx_size, tx_size;
	int err;

	if (!is_valid_ether_addr(dev->dev_addr))
		return -EINVAL;

	netif_info(skge, ifup, skge->netdev, "enabling interface\n");

	if (dev->mtu > RX_BUF_SIZE)
		skge->rx_buf_size = dev->mtu + ETH_HLEN;
	else
		skge->rx_buf_size = RX_BUF_SIZE;


	rx_size = skge->rx_ring.count * sizeof(struct skge_rx_desc);
	tx_size = skge->tx_ring.count * sizeof(struct skge_tx_desc);
	skge->mem_size = tx_size + rx_size;
	skge->mem = pci_alloc_consistent(hw->pdev, skge->mem_size, &skge->dma);
	if (!skge->mem)
		return -ENOMEM;

	BUG_ON(skge->dma & 7);

	if (upper_32_bits(skge->dma) != upper_32_bits(skge->dma + skge->mem_size)) {
		dev_err(&hw->pdev->dev, "pci_alloc_consistent region crosses 4G boundary\n");
		err = -EINVAL;
		goto free_pci_mem;
	}

	err = skge_ring_alloc(&skge->rx_ring, skge->mem, skge->dma);
	if (err)
		goto free_pci_mem;

	err = skge_rx_fill(dev);
	if (err)
		goto free_rx_ring;

	err = skge_ring_alloc(&skge->tx_ring, skge->mem + rx_size,
			      skge->dma + rx_size);
	if (err)
		goto free_rx_ring;

	if (hw->ports == 1) {
		err = request_irq(hw->pdev->irq, skge_intr, IRQF_SHARED,
				  dev->name, hw);
		if (err) {
			netdev_err(dev, "Unable to allocate interrupt %d error: %d\n",
				   hw->pdev->irq, err);
			goto free_tx_ring;
		}
	}

	/* Initialize MAC */
	netif_carrier_off(dev);
	spin_lock_bh(&hw->phy_lock);
	if (is_genesis(hw))
		genesis_mac_init(hw, port);
	else
		yukon_mac_init(hw, port);
	spin_unlock_bh(&hw->phy_lock);

	/* Configure RAMbuffers - equally between ports and tx/rx */
	chunk = (hw->ram_size  - hw->ram_offset) / (hw->ports * 2);
	ram_addr = hw->ram_offset + 2 * chunk * port;

	skge_ramset(hw, rxqaddr[port], ram_addr, chunk);
	skge_qset(skge, rxqaddr[port], skge->rx_ring.to_clean);

	BUG_ON(skge->tx_ring.to_use != skge->tx_ring.to_clean);
	skge_ramset(hw, txqaddr[port], ram_addr+chunk, chunk);
	skge_qset(skge, txqaddr[port], skge->tx_ring.to_use);

	/* Start receiver BMU */
	wmb();
	skge_write8(hw, Q_ADDR(rxqaddr[port], Q_CSR), CSR_START | CSR_IRQ_CL_F);
	skge_led(skge, LED_MODE_ON);

	spin_lock_irq(&hw->hw_lock);
	hw->intr_mask |= portmask[port];
	skge_write32(hw, B0_IMSK, hw->intr_mask);
	skge_read32(hw, B0_IMSK);
	spin_unlock_irq(&hw->hw_lock);

	napi_enable(&skge->napi);

	skge_set_multicast(dev);

	return 0;

 free_tx_ring:
	kfree(skge->tx_ring.start);
 free_rx_ring:
	skge_rx_clean(skge);
	kfree(skge->rx_ring.start);
 free_pci_mem:
	pci_free_consistent(hw->pdev, skge->mem_size, skge->mem, skge->dma);
	skge->mem = NULL;

	return err;
}