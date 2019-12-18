#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {scalar_t__ driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {int /*<<< orphan*/  irq; TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  rfkill_poll; } ;
struct il_priv {unsigned long long hw_base; struct ieee80211_hw* hw; struct pci_dev* pci_dev; int /*<<< orphan*/ * workqueue; TYPE_2__ _3945; TYPE_1__* bands; int /*<<< orphan*/  lock; struct il_cfg* cfg; scalar_t__ eeprom; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  inta_mask; int /*<<< orphan*/ * debugfs_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  cmd_queue; } ;
struct il_cfg {int /*<<< orphan*/  name; } ;
struct il3945_eeprom {unsigned long long mac_address; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INI_SET_MASK ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_NEVO_RESET ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  IL39_CMD_QUEUE_NUM ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int /*<<< orphan*/  IL_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 size_t NL80211_BAND_2GHZ ; 
 int PCIE_LINK_STATE_CLKPM ; 
 int PCIE_LINK_STATE_L0S ; 
 int PCIE_LINK_STATE_L1 ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,TYPE_3__*) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,unsigned long long) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct il_priv*) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  il3945_attribute_group ; 
 int /*<<< orphan*/  il3945_debugfs_ops ; 
 int il3945_hw_set_hw_params (struct il_priv*) ; 
 int il3945_init_drv (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_mac_ops ; 
 int /*<<< orphan*/  il3945_ops ; 
 int /*<<< orphan*/  il3945_setup_deferred_work (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_setup_handlers (struct il_priv*) ; 
 int il3945_setup_mac (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_unset_hw_params (struct il_priv*) ; 
 int /*<<< orphan*/  il_dbgfs_register (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_disable_interrupts (struct il_priv*) ; 
 int /*<<< orphan*/  il_eeprom_free (struct il_priv*) ; 
 int il_eeprom_init (struct il_priv*) ; 
 int /*<<< orphan*/  il_enable_interrupts (struct il_priv*) ; 
 int /*<<< orphan*/  il_free_channel_map (struct il_priv*) ; 
 int /*<<< orphan*/  il_free_geos (struct il_priv*) ; 
 int /*<<< orphan*/  il_isr ; 
 int /*<<< orphan*/  il_power_initialize (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_rxon_channel (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (unsigned long long) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_link_state (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 unsigned long long pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct il_priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct il_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il3945_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int err = 0;
	struct il_priv *il;
	struct ieee80211_hw *hw;
	struct il_cfg *cfg = (struct il_cfg *)(ent->driver_data);
	struct il3945_eeprom *eeprom;
	unsigned long flags;

	/***********************
	 * 1. Allocating HW data
	 * ********************/

	hw = ieee80211_alloc_hw(sizeof(struct il_priv), &il3945_mac_ops);
	if (!hw) {
		err = -ENOMEM;
		goto out;
	}
	il = hw->priv;
	il->hw = hw;
	SET_IEEE80211_DEV(hw, &pdev->dev);

	il->cmd_queue = IL39_CMD_QUEUE_NUM;

	D_INFO("*** LOAD DRIVER ***\n");
	il->cfg = cfg;
	il->ops = &il3945_ops;
#ifdef CONFIG_IWLEGACY_DEBUGFS
	il->debugfs_ops = &il3945_debugfs_ops;
#endif
	il->pci_dev = pdev;
	il->inta_mask = CSR_INI_SET_MASK;

	/***************************
	 * 2. Initializing PCI bus
	 * *************************/
	pci_disable_link_state(pdev,
			       PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	if (pci_enable_device(pdev)) {
		err = -ENODEV;
		goto out_ieee80211_free_hw;
	}

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (!err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	if (err) {
		IL_WARN("No suitable DMA available.\n");
		goto out_pci_disable_device;
	}

	pci_set_drvdata(pdev, il);
	err = pci_request_regions(pdev, DRV_NAME);
	if (err)
		goto out_pci_disable_device;

	/***********************
	 * 3. Read REV Register
	 * ********************/
	il->hw_base = pci_ioremap_bar(pdev, 0);
	if (!il->hw_base) {
		err = -ENODEV;
		goto out_pci_release_regions;
	}

	D_INFO("pci_resource_len = 0x%08llx\n",
	       (unsigned long long)pci_resource_len(pdev, 0));
	D_INFO("pci_resource_base = %p\n", il->hw_base);

	/* We disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state */
	pci_write_config_byte(pdev, 0x41, 0x00);

	/* these spin locks will be used in apm_init and EEPROM access
	 * we should init now
	 */
	spin_lock_init(&il->reg_lock);
	spin_lock_init(&il->lock);

	/*
	 * stop and reset the on-board processor just in case it is in a
	 * strange state ... like being left stranded by a primary kernel
	 * and this is now the kdump kernel trying to start up
	 */
	_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	/***********************
	 * 4. Read EEPROM
	 * ********************/

	/* Read the EEPROM */
	err = il_eeprom_init(il);
	if (err) {
		IL_ERR("Unable to init EEPROM\n");
		goto out_iounmap;
	}
	/* MAC Address location in EEPROM same for 3945/4965 */
	eeprom = (struct il3945_eeprom *)il->eeprom;
	D_INFO("MAC address: %pM\n", eeprom->mac_address);
	SET_IEEE80211_PERM_ADDR(il->hw, eeprom->mac_address);

	/***********************
	 * 5. Setup HW Constants
	 * ********************/
	/* Device-specific setup */
	err = il3945_hw_set_hw_params(il);
	if (err) {
		IL_ERR("failed to set hw settings\n");
		goto out_eeprom_free;
	}

	/***********************
	 * 6. Setup il
	 * ********************/

	err = il3945_init_drv(il);
	if (err) {
		IL_ERR("initializing driver failed\n");
		goto out_unset_hw_params;
	}

	IL_INFO("Detected Intel Wireless WiFi Link %s\n", il->cfg->name);

	/***********************
	 * 7. Setup Services
	 * ********************/

	spin_lock_irqsave(&il->lock, flags);
	il_disable_interrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	pci_enable_msi(il->pci_dev);

	err = request_irq(il->pci_dev->irq, il_isr, IRQF_SHARED, DRV_NAME, il);
	if (err) {
		IL_ERR("Error allocating IRQ %d\n", il->pci_dev->irq);
		goto out_disable_msi;
	}

	err = sysfs_create_group(&pdev->dev.kobj, &il3945_attribute_group);
	if (err) {
		IL_ERR("failed to create sysfs device attributes\n");
		goto out_release_irq;
	}

	il_set_rxon_channel(il, &il->bands[NL80211_BAND_2GHZ].channels[5]);
	il3945_setup_deferred_work(il);
	il3945_setup_handlers(il);
	il_power_initialize(il);

	/*********************************
	 * 8. Setup and Register mac80211
	 * *******************************/

	il_enable_interrupts(il);

	err = il3945_setup_mac(il);
	if (err)
		goto out_remove_sysfs;

	il_dbgfs_register(il, DRV_NAME);

	/* Start monitoring the killswitch */
	queue_delayed_work(il->workqueue, &il->_3945.rfkill_poll, 2 * HZ);

	return 0;

out_remove_sysfs:
	destroy_workqueue(il->workqueue);
	il->workqueue = NULL;
	sysfs_remove_group(&pdev->dev.kobj, &il3945_attribute_group);
out_release_irq:
	free_irq(il->pci_dev->irq, il);
out_disable_msi:
	pci_disable_msi(il->pci_dev);
	il_free_geos(il);
	il_free_channel_map(il);
out_unset_hw_params:
	il3945_unset_hw_params(il);
out_eeprom_free:
	il_eeprom_free(il);
out_iounmap:
	iounmap(il->hw_base);
out_pci_release_regions:
	pci_release_regions(pdev);
out_pci_disable_device:
	pci_disable_device(pdev);
out_ieee80211_free_hw:
	ieee80211_free_hw(il->hw);
out:
	return err;
}