#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int uint64_t ;
typedef  int u16 ;
struct sk_buff {unsigned char* data; int len; } ;
struct pcnet32_private {int rx_ring_size; int tx_ring_size; int /*<<< orphan*/  lock; struct pcnet32_access* a; struct sk_buff** tx_skbuff; struct sk_buff** rx_skbuff; TYPE_1__* rx_ring; TYPE_2__* tx_ring; int /*<<< orphan*/ * tx_dma_addr; int /*<<< orphan*/  pci_dev; } ;
struct pcnet32_access {int (* read_bcr ) (int /*<<< orphan*/ ,int) ;int (* read_csr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_bcr ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* write_csr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;} ;
struct net_device {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  base_addr; } ;
typedef  int __le16 ;
struct TYPE_4__ {void* status; int /*<<< orphan*/  base; scalar_t__ misc; void* length; } ;
struct TYPE_3__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int CSR0_NORMAL ; 
 int CSR0_START ; 
 int CSR0_STOP ; 
 int /*<<< orphan*/  CSR15 ; 
 int /*<<< orphan*/  CSR4 ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int min (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct pcnet32_private*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 scalar_t__ netif_msg_hw (struct pcnet32_private*) ; 
 scalar_t__ netif_msg_pktdata (struct pcnet32_private*) ; 
 int /*<<< orphan*/  netif_printk (struct pcnet32_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,int,...) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnet32_netif_start (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_netif_stop (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_purge_rx_ring (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_purge_tx_ring (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_restart (struct net_device*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub14 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub6 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int,int) ; 
 int stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int pcnet32_loopback_test(struct net_device *dev, uint64_t * data1)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	const struct pcnet32_access *a = lp->a;	/* access to registers */
	ulong ioaddr = dev->base_addr;	/* card base I/O address */
	struct sk_buff *skb;	/* sk buff */
	int x, i;		/* counters */
	int numbuffs = 4;	/* number of TX/RX buffers and descs */
	u16 status = 0x8300;	/* TX ring status */
	__le16 teststatus;	/* test of ring status */
	int rc;			/* return code */
	int size;		/* size of packets */
	unsigned char *packet;	/* source packet data */
	static const int data_len = 60;	/* length of source packets */
	unsigned long flags;
	unsigned long ticks;

	rc = 1;			/* default to fail */

	if (netif_running(dev))
		pcnet32_netif_stop(dev);

	spin_lock_irqsave(&lp->lock, flags);
	lp->a->write_csr(ioaddr, CSR0, CSR0_STOP);	/* stop the chip */

	numbuffs = min(numbuffs, (int)min(lp->rx_ring_size, lp->tx_ring_size));

	/* Reset the PCNET32 */
	lp->a->reset(ioaddr);
	lp->a->write_csr(ioaddr, CSR4, 0x0915);	/* auto tx pad */

	/* switch pcnet32 to 32bit mode */
	lp->a->write_bcr(ioaddr, 20, 2);

	/* purge & init rings but don't actually restart */
	pcnet32_restart(dev, 0x0000);

	lp->a->write_csr(ioaddr, CSR0, CSR0_STOP);	/* Set STOP bit */

	/* Initialize Transmit buffers. */
	size = data_len + 15;
	for (x = 0; x < numbuffs; x++) {
		skb = netdev_alloc_skb(dev, size);
		if (!skb) {
			netif_printk(lp, hw, KERN_DEBUG, dev,
				     "Cannot allocate skb at line: %d!\n",
				     __LINE__);
			goto clean_up;
		}
		packet = skb->data;
		skb_put(skb, size);	/* create space for data */
		lp->tx_skbuff[x] = skb;
		lp->tx_ring[x].length = cpu_to_le16(-skb->len);
		lp->tx_ring[x].misc = 0;

		/* put DA and SA into the skb */
		for (i = 0; i < 6; i++)
			*packet++ = dev->dev_addr[i];
		for (i = 0; i < 6; i++)
			*packet++ = dev->dev_addr[i];
		/* type */
		*packet++ = 0x08;
		*packet++ = 0x06;
		/* packet number */
		*packet++ = x;
		/* fill packet with data */
		for (i = 0; i < data_len; i++)
			*packet++ = i;

		lp->tx_dma_addr[x] =
			pci_map_single(lp->pci_dev, skb->data, skb->len,
				       PCI_DMA_TODEVICE);
		if (pci_dma_mapping_error(lp->pci_dev, lp->tx_dma_addr[x])) {
			netif_printk(lp, hw, KERN_DEBUG, dev,
				     "DMA mapping error at line: %d!\n",
				     __LINE__);
			goto clean_up;
		}
		lp->tx_ring[x].base = cpu_to_le32(lp->tx_dma_addr[x]);
		wmb();	/* Make sure owner changes after all others are visible */
		lp->tx_ring[x].status = cpu_to_le16(status);
	}

	x = a->read_bcr(ioaddr, 32);	/* set internal loopback in BCR32 */
	a->write_bcr(ioaddr, 32, x | 0x0002);

	/* set int loopback in CSR15 */
	x = a->read_csr(ioaddr, CSR15) & 0xfffc;
	lp->a->write_csr(ioaddr, CSR15, x | 0x0044);

	teststatus = cpu_to_le16(0x8000);
	lp->a->write_csr(ioaddr, CSR0, CSR0_START);	/* Set STRT bit */

	/* Check status of descriptors */
	for (x = 0; x < numbuffs; x++) {
		ticks = 0;
		rmb();
		while ((lp->rx_ring[x].status & teststatus) && (ticks < 200)) {
			spin_unlock_irqrestore(&lp->lock, flags);
			msleep(1);
			spin_lock_irqsave(&lp->lock, flags);
			rmb();
			ticks++;
		}
		if (ticks == 200) {
			netif_err(lp, hw, dev, "Desc %d failed to reset!\n", x);
			break;
		}
	}

	lp->a->write_csr(ioaddr, CSR0, CSR0_STOP);	/* Set STOP bit */
	wmb();
	if (netif_msg_hw(lp) && netif_msg_pktdata(lp)) {
		netdev_printk(KERN_DEBUG, dev, "RX loopback packets:\n");

		for (x = 0; x < numbuffs; x++) {
			netdev_printk(KERN_DEBUG, dev, "Packet %d: ", x);
			skb = lp->rx_skbuff[x];
			for (i = 0; i < size; i++)
				pr_cont(" %02x", *(skb->data + i));
			pr_cont("\n");
		}
	}

	x = 0;
	rc = 0;
	while (x < numbuffs && !rc) {
		skb = lp->rx_skbuff[x];
		packet = lp->tx_skbuff[x]->data;
		for (i = 0; i < size; i++) {
			if (*(skb->data + i) != packet[i]) {
				netif_printk(lp, hw, KERN_DEBUG, dev,
					     "Error in compare! %2x - %02x %02x\n",
					     i, *(skb->data + i), packet[i]);
				rc = 1;
				break;
			}
		}
		x++;
	}

clean_up:
	*data1 = rc;
	pcnet32_purge_tx_ring(dev);

	x = a->read_csr(ioaddr, CSR15);
	a->write_csr(ioaddr, CSR15, (x & ~0x0044));	/* reset bits 6 and 2 */

	x = a->read_bcr(ioaddr, 32);	/* reset internal loopback */
	a->write_bcr(ioaddr, 32, (x & ~0x0002));

	if (netif_running(dev)) {
		pcnet32_netif_start(dev);
		pcnet32_restart(dev, CSR0_NORMAL);
	} else {
		pcnet32_purge_rx_ring(dev);
		lp->a->write_bcr(ioaddr, 20, 4);	/* return to 16bit mode */
	}
	spin_unlock_irqrestore(&lp->lock, flags);

	return rc;
}