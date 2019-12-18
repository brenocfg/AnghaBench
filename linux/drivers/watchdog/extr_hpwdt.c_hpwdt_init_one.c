#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct pci_dev {scalar_t__ subsystem_vendor; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ timeout; int /*<<< orphan*/ * parent; scalar_t__ pretimeout; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HPWDT_MAX_TIMER ; 
 char* HPWDT_VERSION ; 
 scalar_t__ PCI_VENDOR_ID_HP ; 
 scalar_t__ PCI_VENDOR_ID_HP_3PAR ; 
 scalar_t__ PRETIMEOUT_SEC ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hpwdt_blacklist ; 
 TYPE_1__ hpwdt_dev ; 
 int /*<<< orphan*/  hpwdt_exit_nmi_decoding () ; 
 scalar_t__ hpwdt_hw_is_running () ; 
 int hpwdt_init_nmi_decoding (struct pci_dev*) ; 
 void* hpwdt_nmistat ; 
 void* hpwdt_timer_con ; 
 void* hpwdt_timer_reg ; 
 int ilo5 ; 
 char* kdumptimeout ; 
 char* min (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 void* pci_iomap (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,void*) ; 
 scalar_t__ pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 
 void* pci_mem_addr ; 
 scalar_t__ pretimeout ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soft_margin ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 

__attribute__((used)) static int hpwdt_init_one(struct pci_dev *dev,
					const struct pci_device_id *ent)
{
	int retval;

	/*
	 * First let's find out if we are on an iLO2+ server. We will
	 * not run on a legacy ASM box.
	 * So we only support the G5 ProLiant servers and higher.
	 */
	if (dev->subsystem_vendor != PCI_VENDOR_ID_HP &&
	    dev->subsystem_vendor != PCI_VENDOR_ID_HP_3PAR) {
		dev_warn(&dev->dev,
			"This server does not have an iLO2+ ASIC.\n");
		return -ENODEV;
	}

	if (pci_match_id(hpwdt_blacklist, dev)) {
		dev_dbg(&dev->dev, "Not supported on this device\n");
		return -ENODEV;
	}

	if (pci_enable_device(dev)) {
		dev_warn(&dev->dev,
			"Not possible to enable PCI Device: 0x%x:0x%x.\n",
			ent->vendor, ent->device);
		return -ENODEV;
	}

	pci_mem_addr = pci_iomap(dev, 1, 0x80);
	if (!pci_mem_addr) {
		dev_warn(&dev->dev,
			"Unable to detect the iLO2+ server memory.\n");
		retval = -ENOMEM;
		goto error_pci_iomap;
	}
	hpwdt_nmistat	= pci_mem_addr + 0x6e;
	hpwdt_timer_reg = pci_mem_addr + 0x70;
	hpwdt_timer_con = pci_mem_addr + 0x72;

	/* Have the core update running timer until user space is ready */
	if (hpwdt_hw_is_running()) {
		dev_info(&dev->dev, "timer is running\n");
		set_bit(WDOG_HW_RUNNING, &hpwdt_dev.status);
	}

	/* Initialize NMI Decoding functionality */
	retval = hpwdt_init_nmi_decoding(dev);
	if (retval != 0)
		goto error_init_nmi_decoding;

	watchdog_stop_on_unregister(&hpwdt_dev);
	watchdog_set_nowayout(&hpwdt_dev, nowayout);
	watchdog_init_timeout(&hpwdt_dev, soft_margin, NULL);

	if (pretimeout && hpwdt_dev.timeout <= PRETIMEOUT_SEC) {
		dev_warn(&dev->dev, "timeout <= pretimeout. Setting pretimeout to zero\n");
		pretimeout = 0;
	}
	hpwdt_dev.pretimeout = pretimeout ? PRETIMEOUT_SEC : 0;
	kdumptimeout = min(kdumptimeout, HPWDT_MAX_TIMER);

	hpwdt_dev.parent = &dev->dev;
	retval = watchdog_register_device(&hpwdt_dev);
	if (retval < 0)
		goto error_wd_register;

	dev_info(&dev->dev, "HPE Watchdog Timer Driver: Version: %s\n",
				HPWDT_VERSION);
	dev_info(&dev->dev, "timeout: %d seconds (nowayout=%d)\n",
				hpwdt_dev.timeout, nowayout);
	dev_info(&dev->dev, "pretimeout: %s.\n",
				pretimeout ? "on" : "off");
	dev_info(&dev->dev, "kdumptimeout: %d.\n", kdumptimeout);

	if (dev->subsystem_vendor == PCI_VENDOR_ID_HP_3PAR)
		ilo5 = true;

	return 0;

error_wd_register:
	hpwdt_exit_nmi_decoding();
error_init_nmi_decoding:
	pci_iounmap(dev, pci_mem_addr);
error_pci_iomap:
	pci_disable_device(dev);
	return retval;
}