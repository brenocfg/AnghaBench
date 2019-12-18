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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct net_device {int features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; scalar_t__ dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct cas_init_block {int /*<<< orphan*/ * rxcs; int /*<<< orphan*/ * rxds; int /*<<< orphan*/ * txds; } ;
struct cas {unsigned long casreg_len; int cas_flags; scalar_t__ phy_type; int hw_running; scalar_t__ regs; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  block_dvma; struct cas_init_block* init_block; int /*<<< orphan*/  napi; int /*<<< orphan*/ * rx_flows; int /*<<< orphan*/ * init_rxcs; int /*<<< orphan*/ * init_rxds; int /*<<< orphan*/ * init_txds; scalar_t__ timer_ticks; struct net_device* dev; int /*<<< orphan*/  link_transition; int /*<<< orphan*/  lstate; int /*<<< orphan*/  link_cntl; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  reset_task_pending_mtu; int /*<<< orphan*/  reset_task_pending_spare; int /*<<< orphan*/  reset_task_pending_all; int /*<<< orphan*/  reset_task_pending; int /*<<< orphan*/  link_timer; int /*<<< orphan*/ * stat_lock; int /*<<< orphan*/ * tx_lock; int /*<<< orphan*/  rx_spare_lock; int /*<<< orphan*/  rx_inuse_lock; int /*<<< orphan*/  lock; scalar_t__ link_transition_jiffies_valid; int /*<<< orphan*/  of_node; scalar_t__ msg_enable; scalar_t__ orig_cacheline_size; struct pci_dev* pdev; } ;

/* Variables and functions */
 int BIM_CFG_32BIT ; 
 int BIM_CFG_66MHZ ; 
 int /*<<< orphan*/  BMCR_ANENABLE ; 
 scalar_t__ CAS_DEF_MSG_ENABLE ; 
 int CAS_FLAG_NO_HW_CSUM ; 
 int CAS_FLAG_REG_PLUS ; 
 int CAS_FLAG_SATURN ; 
 int /*<<< orphan*/  CAS_MAX_MTU ; 
 int /*<<< orphan*/  CAS_MIN_MTU ; 
 scalar_t__ CAS_PHY_SERDES ; 
 scalar_t__ CAS_PREF_CACHELINE_SIZE ; 
 int /*<<< orphan*/  CAS_TX_TIMEOUT ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  LINK_TRANSITION_LINK_DOWN ; 
 int /*<<< orphan*/  LINK_TRANSITION_UNKNOWN ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 int N_RX_COMP_RINGS ; 
 int N_RX_DESC_RINGS ; 
 int N_RX_FLOWS ; 
 int N_TX_RINGS ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_PARITY ; 
 int /*<<< orphan*/  PCI_COMMAND_SERR ; 
 scalar_t__ REG_BIM_CFG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ SMP_CACHE_BYTES ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_begin_auto_negotiation (struct cas*,int /*<<< orphan*/ *) ; 
 scalar_t__ cas_check_invariants (struct cas*) ; 
 int /*<<< orphan*/  cas_check_pci_invariants (struct cas*) ; 
 int /*<<< orphan*/  cas_entropy_reset (struct cas*) ; 
 int /*<<< orphan*/  cas_ethtool_ops ; 
 int /*<<< orphan*/  cas_hard_reset (struct cas*) ; 
 int /*<<< orphan*/  cas_link_timer ; 
 int /*<<< orphan*/  cas_netdev_ops ; 
 int /*<<< orphan*/  cas_phy_init (struct cas*) ; 
 int /*<<< orphan*/  cas_poll ; 
 int /*<<< orphan*/  cas_program_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  cas_reset (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_reset_task ; 
 int /*<<< orphan*/  cas_saturn_firmware_init (struct cas*) ; 
 int /*<<< orphan*/  cas_shutdown (struct cas*) ; 
 scalar_t__ cassini_debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  link_down ; 
 int link_mode ; 
 int /*<<< orphan*/ * link_modes ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_alloc_consistent (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,struct cas_init_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ pci_try_set_mwi (struct pci_dev*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static int cas_init_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	static int cas_version_printed = 0;
	unsigned long casreg_len;
	struct net_device *dev;
	struct cas *cp;
	int i, err, pci_using_dac;
	u16 pci_cmd;
	u8 orig_cacheline_size = 0, cas_cacheline_size = 0;

	if (cas_version_printed++ == 0)
		pr_info("%s", version);

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		return err;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev, "Cannot find proper PCI device "
		       "base address, aborting\n");
		err = -ENODEV;
		goto err_out_disable_pdev;
	}

	dev = alloc_etherdev(sizeof(*cp));
	if (!dev) {
		err = -ENOMEM;
		goto err_out_disable_pdev;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = pci_request_regions(pdev, dev->name);
	if (err) {
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		goto err_out_free_netdev;
	}
	pci_set_master(pdev);

	/* we must always turn on parity response or else parity
	 * doesn't get generated properly. disable SERR/PERR as well.
	 * in addition, we want to turn MWI on.
	 */
	pci_read_config_word(pdev, PCI_COMMAND, &pci_cmd);
	pci_cmd &= ~PCI_COMMAND_SERR;
	pci_cmd |= PCI_COMMAND_PARITY;
	pci_write_config_word(pdev, PCI_COMMAND, pci_cmd);
	if (pci_try_set_mwi(pdev))
		pr_warn("Could not enable MWI for %s\n", pci_name(pdev));

	cas_program_bridge(pdev);

	/*
	 * On some architectures, the default cache line size set
	 * by pci_try_set_mwi reduces perforamnce.  We have to increase
	 * it for this case.  To start, we'll print some configuration
	 * data.
	 */
#if 1
	pci_read_config_byte(pdev, PCI_CACHE_LINE_SIZE,
			     &orig_cacheline_size);
	if (orig_cacheline_size < CAS_PREF_CACHELINE_SIZE) {
		cas_cacheline_size =
			(CAS_PREF_CACHELINE_SIZE < SMP_CACHE_BYTES) ?
			CAS_PREF_CACHELINE_SIZE : SMP_CACHE_BYTES;
		if (pci_write_config_byte(pdev,
					  PCI_CACHE_LINE_SIZE,
					  cas_cacheline_size)) {
			dev_err(&pdev->dev, "Could not set PCI cache "
			       "line size\n");
			goto err_write_cacheline;
		}
	}
#endif


	/* Configure DMA attributes. */
	if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) {
		pci_using_dac = 1;
		err = pci_set_consistent_dma_mask(pdev,
						  DMA_BIT_MASK(64));
		if (err < 0) {
			dev_err(&pdev->dev, "Unable to obtain 64-bit DMA "
			       "for consistent allocations\n");
			goto err_out_free_res;
		}

	} else {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev, "No usable DMA configuration, "
			       "aborting\n");
			goto err_out_free_res;
		}
		pci_using_dac = 0;
	}

	casreg_len = pci_resource_len(pdev, 0);

	cp = netdev_priv(dev);
	cp->pdev = pdev;
#if 1
	/* A value of 0 indicates we never explicitly set it */
	cp->orig_cacheline_size = cas_cacheline_size ? orig_cacheline_size: 0;
#endif
	cp->dev = dev;
	cp->msg_enable = (cassini_debug < 0) ? CAS_DEF_MSG_ENABLE :
	  cassini_debug;

#if defined(CONFIG_SPARC)
	cp->of_node = pci_device_to_OF_node(pdev);
#endif

	cp->link_transition = LINK_TRANSITION_UNKNOWN;
	cp->link_transition_jiffies_valid = 0;

	spin_lock_init(&cp->lock);
	spin_lock_init(&cp->rx_inuse_lock);
	spin_lock_init(&cp->rx_spare_lock);
	for (i = 0; i < N_TX_RINGS; i++) {
		spin_lock_init(&cp->stat_lock[i]);
		spin_lock_init(&cp->tx_lock[i]);
	}
	spin_lock_init(&cp->stat_lock[N_TX_RINGS]);
	mutex_init(&cp->pm_mutex);

	timer_setup(&cp->link_timer, cas_link_timer, 0);

#if 1
	/* Just in case the implementation of atomic operations
	 * change so that an explicit initialization is necessary.
	 */
	atomic_set(&cp->reset_task_pending, 0);
	atomic_set(&cp->reset_task_pending_all, 0);
	atomic_set(&cp->reset_task_pending_spare, 0);
	atomic_set(&cp->reset_task_pending_mtu, 0);
#endif
	INIT_WORK(&cp->reset_task, cas_reset_task);

	/* Default link parameters */
	if (link_mode >= 0 && link_mode < 6)
		cp->link_cntl = link_modes[link_mode];
	else
		cp->link_cntl = BMCR_ANENABLE;
	cp->lstate = link_down;
	cp->link_transition = LINK_TRANSITION_LINK_DOWN;
	netif_carrier_off(cp->dev);
	cp->timer_ticks = 0;

	/* give us access to cassini registers */
	cp->regs = pci_iomap(pdev, 0, casreg_len);
	if (!cp->regs) {
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		goto err_out_free_res;
	}
	cp->casreg_len = casreg_len;

	pci_save_state(pdev);
	cas_check_pci_invariants(cp);
	cas_hard_reset(cp);
	cas_reset(cp, 0);
	if (cas_check_invariants(cp))
		goto err_out_iounmap;
	if (cp->cas_flags & CAS_FLAG_SATURN)
		cas_saturn_firmware_init(cp);

	cp->init_block = (struct cas_init_block *)
		pci_alloc_consistent(pdev, sizeof(struct cas_init_block),
				     &cp->block_dvma);
	if (!cp->init_block) {
		dev_err(&pdev->dev, "Cannot allocate init block, aborting\n");
		goto err_out_iounmap;
	}

	for (i = 0; i < N_TX_RINGS; i++)
		cp->init_txds[i] = cp->init_block->txds[i];

	for (i = 0; i < N_RX_DESC_RINGS; i++)
		cp->init_rxds[i] = cp->init_block->rxds[i];

	for (i = 0; i < N_RX_COMP_RINGS; i++)
		cp->init_rxcs[i] = cp->init_block->rxcs[i];

	for (i = 0; i < N_RX_FLOWS; i++)
		skb_queue_head_init(&cp->rx_flows[i]);

	dev->netdev_ops = &cas_netdev_ops;
	dev->ethtool_ops = &cas_ethtool_ops;
	dev->watchdog_timeo = CAS_TX_TIMEOUT;

#ifdef USE_NAPI
	netif_napi_add(dev, &cp->napi, cas_poll, 64);
#endif
	dev->irq = pdev->irq;
	dev->dma = 0;

	/* Cassini features. */
	if ((cp->cas_flags & CAS_FLAG_NO_HW_CSUM) == 0)
		dev->features |= NETIF_F_HW_CSUM | NETIF_F_SG;

	if (pci_using_dac)
		dev->features |= NETIF_F_HIGHDMA;

	/* MTU range: 60 - varies or 9000 */
	dev->min_mtu = CAS_MIN_MTU;
	dev->max_mtu = CAS_MAX_MTU;

	if (register_netdev(dev)) {
		dev_err(&pdev->dev, "Cannot register net device, aborting\n");
		goto err_out_free_consistent;
	}

	i = readl(cp->regs + REG_BIM_CFG);
	netdev_info(dev, "Sun Cassini%s (%sbit/%sMHz PCI/%s) Ethernet[%d] %pM\n",
		    (cp->cas_flags & CAS_FLAG_REG_PLUS) ? "+" : "",
		    (i & BIM_CFG_32BIT) ? "32" : "64",
		    (i & BIM_CFG_66MHZ) ? "66" : "33",
		    (cp->phy_type == CAS_PHY_SERDES) ? "Fi" : "Cu", pdev->irq,
		    dev->dev_addr);

	pci_set_drvdata(pdev, dev);
	cp->hw_running = 1;
	cas_entropy_reset(cp);
	cas_phy_init(cp);
	cas_begin_auto_negotiation(cp, NULL);
	return 0;

err_out_free_consistent:
	pci_free_consistent(pdev, sizeof(struct cas_init_block),
			    cp->init_block, cp->block_dvma);

err_out_iounmap:
	mutex_lock(&cp->pm_mutex);
	if (cp->hw_running)
		cas_shutdown(cp);
	mutex_unlock(&cp->pm_mutex);

	pci_iounmap(pdev, cp->regs);


err_out_free_res:
	pci_release_regions(pdev);

err_write_cacheline:
	/* Try to restore it in case the error occurred after we
	 * set it.
	 */
	pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE, orig_cacheline_size);

err_out_free_netdev:
	free_netdev(dev);

err_out_disable_pdev:
	pci_disable_device(pdev);
	return -ENODEV;
}