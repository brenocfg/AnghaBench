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
typedef  int u32 ;
struct tx_desc {int dummy; } ;
struct pci_device_id {int driver_data; } ;
struct pci_dev {int revision; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct dmfe_board_info {int chip_id; int chip_revision; int chip_type; int /*<<< orphan*/  desc_pool_dma_ptr; void* desc_pool_ptr; int /*<<< orphan*/  buf_pool_dma_ptr; void* buf_pool_ptr; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/ * srom; int /*<<< orphan*/  lock; struct pci_dev* pdev; scalar_t__ wol_mode; int /*<<< orphan*/  buf_pool_dma_start; void* buf_pool_start; int /*<<< orphan*/  first_tx_desc_dma; struct tx_desc* first_tx_desc; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ CHK_IO_SIZE (struct pci_dev*) ; 
 int DESC_ALL_CNT ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMFE_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int PCI_DM9100_ID ; 
 int PCI_DM9102_ID ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int TX_BUF_ALLOC ; 
 int TX_DESC_CNT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 int /*<<< orphan*/  netdev_ops ; 
 struct dmfe_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* pci_alloc_consistent (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  printed_version ; 
 int /*<<< orphan*/  read_srom_word (int /*<<< orphan*/ ,int) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static int dmfe_init_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct dmfe_board_info *db;	/* board information structure */
	struct net_device *dev;
	u32 pci_pmr;
	int i, err;

	DMFE_DBUG(0, "dmfe_init_one()", 0);

	if (!printed_version++)
		pr_info("%s\n", version);

	/*
	 *	SPARC on-board DM910x chips should be handled by the main
	 *	tulip driver, except for early DM9100s.
	 */
#ifdef CONFIG_TULIP_DM910X
	if ((ent->driver_data == PCI_DM9100_ID && pdev->revision >= 0x30) ||
	    ent->driver_data == PCI_DM9102_ID) {
		struct device_node *dp = pci_device_to_OF_node(pdev);

		if (dp && of_get_property(dp, "local-mac-address", NULL)) {
			pr_info("skipping on-board DM910x (use tulip)\n");
			return -ENODEV;
		}
	}
#endif

	/* Init network device */
	dev = alloc_etherdev(sizeof(*db));
	if (dev == NULL)
		return -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	if (pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) {
		pr_warn("32-bit PCI DMA not available\n");
		err = -ENODEV;
		goto err_out_free;
	}

	/* Enable Master/IO access, Disable memory access */
	err = pci_enable_device(pdev);
	if (err)
		goto err_out_free;

	if (!pci_resource_start(pdev, 0)) {
		pr_err("I/O base is zero\n");
		err = -ENODEV;
		goto err_out_disable;
	}

	if (pci_resource_len(pdev, 0) < (CHK_IO_SIZE(pdev)) ) {
		pr_err("Allocated I/O size too small\n");
		err = -ENODEV;
		goto err_out_disable;
	}

#if 0	/* pci_{enable_device,set_master} sets minimum latency for us now */

	/* Set Latency Timer 80h */
	/* FIXME: setting values > 32 breaks some SiS 559x stuff.
	   Need a PCI quirk.. */

	pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 0x80);
#endif

	if (pci_request_regions(pdev, DRV_NAME)) {
		pr_err("Failed to request PCI regions\n");
		err = -ENODEV;
		goto err_out_disable;
	}

	/* Init system & device */
	db = netdev_priv(dev);

	/* Allocate Tx/Rx descriptor memory */
	db->desc_pool_ptr = pci_alloc_consistent(pdev, sizeof(struct tx_desc) *
			DESC_ALL_CNT + 0x20, &db->desc_pool_dma_ptr);
	if (!db->desc_pool_ptr) {
		err = -ENOMEM;
		goto err_out_res;
	}

	db->buf_pool_ptr = pci_alloc_consistent(pdev, TX_BUF_ALLOC *
			TX_DESC_CNT + 4, &db->buf_pool_dma_ptr);
	if (!db->buf_pool_ptr) {
		err = -ENOMEM;
		goto err_out_free_desc;
	}

	db->first_tx_desc = (struct tx_desc *) db->desc_pool_ptr;
	db->first_tx_desc_dma = db->desc_pool_dma_ptr;
	db->buf_pool_start = db->buf_pool_ptr;
	db->buf_pool_dma_start = db->buf_pool_dma_ptr;

	db->chip_id = ent->driver_data;
	/* IO type range. */
	db->ioaddr = pci_iomap(pdev, 0, 0);
	if (!db->ioaddr) {
		err = -ENOMEM;
		goto err_out_free_buf;
	}

	db->chip_revision = pdev->revision;
	db->wol_mode = 0;

	db->pdev = pdev;

	pci_set_drvdata(pdev, dev);
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	netif_carrier_off(dev);
	spin_lock_init(&db->lock);

	pci_read_config_dword(pdev, 0x50, &pci_pmr);
	pci_pmr &= 0x70000;
	if ( (pci_pmr == 0x10000) && (db->chip_revision == 0x31) )
		db->chip_type = 1;	/* DM9102A E3 */
	else
		db->chip_type = 0;

	/* read 64 word srom data */
	for (i = 0; i < 64; i++) {
		((__le16 *) db->srom)[i] =
			cpu_to_le16(read_srom_word(db->ioaddr, i));
	}

	/* Set Node address */
	for (i = 0; i < 6; i++)
		dev->dev_addr[i] = db->srom[20 + i];

	err = register_netdev (dev);
	if (err)
		goto err_out_unmap;

	dev_info(&dev->dev, "Davicom DM%04lx at pci%s, %pM, irq %d\n",
		 ent->driver_data >> 16,
		 pci_name(pdev), dev->dev_addr, pdev->irq);

	pci_set_master(pdev);

	return 0;

err_out_unmap:
	pci_iounmap(pdev, db->ioaddr);
err_out_free_buf:
	pci_free_consistent(pdev, TX_BUF_ALLOC * TX_DESC_CNT + 4,
			    db->buf_pool_ptr, db->buf_pool_dma_ptr);
err_out_free_desc:
	pci_free_consistent(pdev, sizeof(struct tx_desc) * DESC_ALL_CNT + 0x20,
			    db->desc_pool_ptr, db->desc_pool_dma_ptr);
err_out_res:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_free:
	free_netdev(dev);

	return err;
}