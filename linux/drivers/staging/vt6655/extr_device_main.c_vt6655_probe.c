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
struct wiphy {int interface_modes; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; } ;
struct vnt_private {int memaddr; int byRFType; struct ieee80211_hw* hw; int /*<<< orphan*/  PortOffset; int /*<<< orphan*/  abyCurrentNetAddr; int /*<<< orphan*/  interrupt_work; void* ioaddr; int /*<<< orphan*/  lock; struct pci_dev* pcid; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ieee80211_hw {int max_signal; struct wiphy* wiphy; struct vnt_private* priv; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_FULL_DRV_NAM ; 
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  DEVICE_VERSION ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  EEP_OFS_RFTYPE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FRAG_THRESH_DEF ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACbSoftwareReset (struct vnt_private*) ; 
 int /*<<< orphan*/  MACvInitialize (struct vnt_private*) ; 
 int /*<<< orphan*/  MACvReadEtherAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int RF_MASK ; 
 int /*<<< orphan*/  RTS_THRESH_DEF ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int SROMbyReadEmbedded (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  TIMING_BEACON_ONLY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_free_info (struct vnt_private*) ; 
 int /*<<< orphan*/  device_get_options (struct vnt_private*) ; 
 int /*<<< orphan*/  device_print_info (struct vnt_private*) ; 
 int /*<<< orphan*/  device_set_options (struct vnt_private*) ; 
 scalar_t__ dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int,int) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct vnt_private*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vnt_init (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_interrupt_work ; 
 int /*<<< orphan*/  vnt_mac_ops ; 

__attribute__((used)) static int
vt6655_probe(struct pci_dev *pcid, const struct pci_device_id *ent)
{
	struct vnt_private *priv;
	struct ieee80211_hw *hw;
	struct wiphy *wiphy;
	int         rc;

	dev_notice(&pcid->dev,
		   "%s Ver. %s\n", DEVICE_FULL_DRV_NAM, DEVICE_VERSION);

	dev_notice(&pcid->dev,
		   "Copyright (c) 2003 VIA Networking Technologies, Inc.\n");

	hw = ieee80211_alloc_hw(sizeof(*priv), &vnt_mac_ops);
	if (!hw) {
		dev_err(&pcid->dev, "could not register ieee80211_hw\n");
		return -ENOMEM;
	}

	priv = hw->priv;
	priv->pcid = pcid;

	spin_lock_init(&priv->lock);

	priv->hw = hw;

	SET_IEEE80211_DEV(priv->hw, &pcid->dev);

	if (pci_enable_device(pcid)) {
		device_free_info(priv);
		return -ENODEV;
	}

	dev_dbg(&pcid->dev,
		"Before get pci_info memaddr is %x\n", priv->memaddr);

	pci_set_master(pcid);

	priv->memaddr = pci_resource_start(pcid, 0);
	priv->ioaddr = pci_resource_start(pcid, 1);
	priv->PortOffset = ioremap(priv->memaddr & PCI_BASE_ADDRESS_MEM_MASK,
				   256);
	if (!priv->PortOffset) {
		dev_err(&pcid->dev, ": Failed to IO remapping ..\n");
		device_free_info(priv);
		return -ENODEV;
	}

	rc = pci_request_regions(pcid, DEVICE_NAME);
	if (rc) {
		dev_err(&pcid->dev, ": Failed to find PCI device\n");
		device_free_info(priv);
		return -ENODEV;
	}

	if (dma_set_mask(&pcid->dev, DMA_BIT_MASK(32))) {
		dev_err(&pcid->dev, ": Failed to set dma 32 bit mask\n");
		device_free_info(priv);
		return -ENODEV;
	}

	INIT_WORK(&priv->interrupt_work, vnt_interrupt_work);

	/* do reset */
	if (!MACbSoftwareReset(priv)) {
		dev_err(&pcid->dev, ": Failed to access MAC hardware..\n");
		device_free_info(priv);
		return -ENODEV;
	}
	/* initial to reload eeprom */
	MACvInitialize(priv);
	MACvReadEtherAddress(priv->PortOffset, priv->abyCurrentNetAddr);

	/* Get RFType */
	priv->byRFType = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_RFTYPE);
	priv->byRFType &= RF_MASK;

	dev_dbg(&pcid->dev, "RF Type = %x\n", priv->byRFType);

	device_get_options(priv);
	device_set_options(priv);

	wiphy = priv->hw->wiphy;

	wiphy->frag_threshold = FRAG_THRESH_DEF;
	wiphy->rts_threshold = RTS_THRESH_DEF;
	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) | BIT(NL80211_IFTYPE_AP);

	ieee80211_hw_set(priv->hw, TIMING_BEACON_ONLY);
	ieee80211_hw_set(priv->hw, SIGNAL_DBM);
	ieee80211_hw_set(priv->hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(priv->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(priv->hw, SUPPORTS_PS);

	priv->hw->max_signal = 100;

	if (vnt_init(priv)) {
		device_free_info(priv);
		return -ENODEV;
	}

	device_print_info(priv);
	pci_set_drvdata(pcid, priv);

	return 0;
}