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
typedef  int /*<<< orphan*/  u_long ;
struct sk_buff {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {scalar_t__ mem_start; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  base_addr; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int autosense; int /*<<< orphan*/  fdx; } ;
struct TYPE_5__ {int /*<<< orphan*/  gepc; int /*<<< orphan*/  queue; } ;
struct de4x5_private {scalar_t__ bus; int useSROM; int timeout; int autosense; scalar_t__ chipset; int dma_size; int rxRingSize; int txRingSize; int irq_mask; int irq_en; int cfrv; int rx_ovf; scalar_t__ dma_rings; TYPE_3__* rx_ring; int /*<<< orphan*/  state; int /*<<< orphan*/  frame; TYPE_3__* tx_ring; struct sk_buff** rx_skb; int /*<<< orphan*/  adapter_name; TYPE_2__ params; int /*<<< orphan*/  fdx; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; struct device* gendev; int /*<<< orphan*/  asBitValid; void* asPolarity; void* asBit; TYPE_1__ cache; } ;
struct de4x5_desc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  des1; scalar_t__ next; scalar_t__ buf; scalar_t__ status; } ;

/* Variables and functions */
 int BNC ; 
 int BNC_AUI ; 
 int /*<<< orphan*/  CLOSED ; 
 scalar_t__ DC21040 ; 
 scalar_t__ DC21041 ; 
 scalar_t__ DC21140 ; 
 int /*<<< orphan*/  DE4X5_NAME_LENGTH ; 
 int /*<<< orphan*/  DE4X5_RRBA ; 
 int /*<<< orphan*/  DE4X5_STS ; 
 int /*<<< orphan*/  DE4X5_TRBA ; 
 int DEBUG_VERSION ; 
 scalar_t__ EISA ; 
 int /*<<< orphan*/  EISA_signature (char*,struct device*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GEP_INIT ; 
 void* GEP_SLNK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IMR_AIM ; 
 int IMR_NIM ; 
 int IMR_RIM ; 
 int IMR_TIM ; 
 int IMR_TUM ; 
 int IMR_UNM ; 
 int /*<<< orphan*/  INITIALISED ; 
 int NUM_RX_DESC ; 
 int NUM_TX_DESC ; 
 scalar_t__ PCI ; 
 int /*<<< orphan*/  PCI_CFDA_PSM ; 
 int /*<<< orphan*/  PCI_CFPM ; 
 int /*<<< orphan*/  PCI_signature (char*,struct de4x5_private*) ; 
 int /*<<< orphan*/  RD_RER ; 
 int /*<<< orphan*/  RESET_DE4X5 ; 
 int /*<<< orphan*/  RX_BUFF_SZ ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  SLEEP ; 
 int STS_RS ; 
 int STS_TS ; 
 int /*<<< orphan*/  TD_TER ; 
 int TP ; 
 int TP_NW ; 
 int /*<<< orphan*/  WAKEUP ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_packet (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  de4x5_ast ; 
 int de4x5_debug ; 
 int /*<<< orphan*/  de4x5_netdev_ops ; 
 int /*<<< orphan*/  de4x5_parse_params (struct net_device*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct net_device*) ; 
 TYPE_3__* dma_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,TYPE_3__*,scalar_t__) ; 
 int get_hw_addr (struct net_device*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mii_get_phy (struct net_device*) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ srom_infoleaf_info (struct net_device*) ; 
 int /*<<< orphan*/  srom_init (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 char* version ; 
 int /*<<< orphan*/  yawn (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
de4x5_hw_init(struct net_device *dev, u_long iobase, struct device *gendev)
{
    char name[DE4X5_NAME_LENGTH + 1];
    struct de4x5_private *lp = netdev_priv(dev);
    struct pci_dev *pdev = NULL;
    int i, status=0;

    dev_set_drvdata(gendev, dev);

    /* Ensure we're not sleeping */
    if (lp->bus == EISA) {
	outb(WAKEUP, PCI_CFPM);
    } else {
	pdev = to_pci_dev (gendev);
	pci_write_config_byte(pdev, PCI_CFDA_PSM, WAKEUP);
    }
    mdelay(10);

    RESET_DE4X5;

    if ((inl(DE4X5_STS) & (STS_TS | STS_RS)) != 0) {
	return -ENXIO;                       /* Hardware could not reset */
    }

    /*
    ** Now find out what kind of DC21040/DC21041/DC21140 board we have.
    */
    lp->useSROM = false;
    if (lp->bus == PCI) {
	PCI_signature(name, lp);
    } else {
	EISA_signature(name, gendev);
    }

    if (*name == '\0') {                     /* Not found a board signature */
	return -ENXIO;
    }

    dev->base_addr = iobase;
    printk ("%s: %s at 0x%04lx", dev_name(gendev), name, iobase);

    status = get_hw_addr(dev);
    printk(", h/w address %pM\n", dev->dev_addr);

    if (status != 0) {
	printk("      which has an Ethernet PROM CRC error.\n");
	return -ENXIO;
    } else {
	skb_queue_head_init(&lp->cache.queue);
	lp->cache.gepc = GEP_INIT;
	lp->asBit = GEP_SLNK;
	lp->asPolarity = GEP_SLNK;
	lp->asBitValid = ~0;
	lp->timeout = -1;
	lp->gendev = gendev;
	spin_lock_init(&lp->lock);
	timer_setup(&lp->timer, de4x5_ast, 0);
	de4x5_parse_params(dev);

	/*
	** Choose correct autosensing in case someone messed up
	*/
        lp->autosense = lp->params.autosense;
        if (lp->chipset != DC21140) {
            if ((lp->chipset==DC21040) && (lp->params.autosense&TP_NW)) {
                lp->params.autosense = TP;
            }
            if ((lp->chipset==DC21041) && (lp->params.autosense&BNC_AUI)) {
                lp->params.autosense = BNC;
            }
        }
	lp->fdx = lp->params.fdx;
	sprintf(lp->adapter_name,"%s (%s)", name, dev_name(gendev));

	lp->dma_size = (NUM_RX_DESC + NUM_TX_DESC) * sizeof(struct de4x5_desc);
#if defined(__alpha__) || defined(__powerpc__) || defined(CONFIG_SPARC) || defined(DE4X5_DO_MEMCPY)
	lp->dma_size += RX_BUFF_SZ * NUM_RX_DESC + DE4X5_ALIGN;
#endif
	lp->rx_ring = dma_alloc_coherent(gendev, lp->dma_size,
					 &lp->dma_rings, GFP_ATOMIC);
	if (lp->rx_ring == NULL) {
	    return -ENOMEM;
	}

	lp->tx_ring = lp->rx_ring + NUM_RX_DESC;

	/*
	** Set up the RX descriptor ring (Intels)
	** Allocate contiguous receive buffers, long word aligned (Alphas)
	*/
#if !defined(__alpha__) && !defined(__powerpc__) && !defined(CONFIG_SPARC) && !defined(DE4X5_DO_MEMCPY)
	for (i=0; i<NUM_RX_DESC; i++) {
	    lp->rx_ring[i].status = 0;
	    lp->rx_ring[i].des1 = cpu_to_le32(RX_BUFF_SZ);
	    lp->rx_ring[i].buf = 0;
	    lp->rx_ring[i].next = 0;
	    lp->rx_skb[i] = (struct sk_buff *) 1;     /* Dummy entry */
	}

#else
	{
		dma_addr_t dma_rx_bufs;

		dma_rx_bufs = lp->dma_rings + (NUM_RX_DESC + NUM_TX_DESC)
		      	* sizeof(struct de4x5_desc);
		dma_rx_bufs = (dma_rx_bufs + DE4X5_ALIGN) & ~DE4X5_ALIGN;
		lp->rx_bufs = (char *)(((long)(lp->rx_ring + NUM_RX_DESC
		      	+ NUM_TX_DESC) + DE4X5_ALIGN) & ~DE4X5_ALIGN);
		for (i=0; i<NUM_RX_DESC; i++) {
	    		lp->rx_ring[i].status = 0;
	    		lp->rx_ring[i].des1 = cpu_to_le32(RX_BUFF_SZ);
	    		lp->rx_ring[i].buf =
				cpu_to_le32(dma_rx_bufs+i*RX_BUFF_SZ);
	    		lp->rx_ring[i].next = 0;
	    		lp->rx_skb[i] = (struct sk_buff *) 1; /* Dummy entry */
		}

	}
#endif

	barrier();

	lp->rxRingSize = NUM_RX_DESC;
	lp->txRingSize = NUM_TX_DESC;

	/* Write the end of list marker to the descriptor lists */
	lp->rx_ring[lp->rxRingSize - 1].des1 |= cpu_to_le32(RD_RER);
	lp->tx_ring[lp->txRingSize - 1].des1 |= cpu_to_le32(TD_TER);

	/* Tell the adapter where the TX/RX rings are located. */
	outl(lp->dma_rings, DE4X5_RRBA);
	outl(lp->dma_rings + NUM_RX_DESC * sizeof(struct de4x5_desc),
	     DE4X5_TRBA);

	/* Initialise the IRQ mask and Enable/Disable */
	lp->irq_mask = IMR_RIM | IMR_TIM | IMR_TUM | IMR_UNM;
	lp->irq_en   = IMR_NIM | IMR_AIM;

	/* Create a loopback packet frame for later media probing */
	create_packet(dev, lp->frame, sizeof(lp->frame));

	/* Check if the RX overflow bug needs testing for */
	i = lp->cfrv & 0x000000fe;
	if ((lp->chipset == DC21140) && (i == 0x20)) {
	    lp->rx_ovf = 1;
	}

	/* Initialise the SROM pointers if possible */
	if (lp->useSROM) {
	    lp->state = INITIALISED;
	    if (srom_infoleaf_info(dev)) {
	        dma_free_coherent (gendev, lp->dma_size,
			       lp->rx_ring, lp->dma_rings);
		return -ENXIO;
	    }
	    srom_init(dev);
	}

	lp->state = CLOSED;

	/*
	** Check for an MII interface
	*/
	if ((lp->chipset != DC21040) && (lp->chipset != DC21041)) {
	    mii_get_phy(dev);
	}

	printk("      and requires IRQ%d (provided by %s).\n", dev->irq,
	       ((lp->bus == PCI) ? "PCI BIOS" : "EISA CNFG"));
    }

    if (de4x5_debug & DEBUG_VERSION) {
	printk(version);
    }

    /* The DE4X5-specific entries in the device structure. */
    SET_NETDEV_DEV(dev, gendev);
    dev->netdev_ops = &de4x5_netdev_ops;
    dev->mem_start = 0;

    /* Fill in the generic fields of the device structure. */
    if ((status = register_netdev (dev))) {
	    dma_free_coherent (gendev, lp->dma_size,
			       lp->rx_ring, lp->dma_rings);
	    return status;
    }

    /* Let the adapter sleep to save power */
    yawn(dev, SLEEP);

    return status;
}