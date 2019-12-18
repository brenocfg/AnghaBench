#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct cpci_hp_controller {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  irq; } ;
struct TYPE_12__ {int /*<<< orphan*/  subordinate; } ;
struct TYPE_11__ {TYPE_6__* dev_id; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; TYPE_1__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  check_irq; int /*<<< orphan*/  disable_irq; int /*<<< orphan*/  enable_irq; int /*<<< orphan*/  query_enum; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_DEC_21154 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_DEC ; 
 int /*<<< orphan*/  bus0 ; 
 TYPE_3__* bus0_dev ; 
 int cpci_hp_register_bus (int /*<<< orphan*/ ,int,int) ; 
 int cpci_hp_register_controller (TYPE_2__*) ; 
 int cpci_hp_start () ; 
 int /*<<< orphan*/  cpci_hp_unregister_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpci_hp_unregister_controller (TYPE_2__*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 TYPE_6__* hc_dev ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_3__*) ; 
 TYPE_3__* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll ; 
 int /*<<< orphan*/  zt5550_hc_check_irq ; 
 int /*<<< orphan*/  zt5550_hc_cleanup () ; 
 int zt5550_hc_config (struct pci_dev*) ; 
 int /*<<< orphan*/  zt5550_hc_disable_irq ; 
 int /*<<< orphan*/  zt5550_hc_enable_irq ; 
 int /*<<< orphan*/  zt5550_hc_query_enum ; 
 TYPE_2__ zt5550_hpc ; 
 TYPE_1__ zt5550_hpc_ops ; 

__attribute__((used)) static int zt5550_hc_init_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int status;

	status = zt5550_hc_config(pdev);
	if (status != 0)
		return status;

	dbg("returned from zt5550_hc_config");

	memset(&zt5550_hpc, 0, sizeof(struct cpci_hp_controller));
	zt5550_hpc_ops.query_enum = zt5550_hc_query_enum;
	zt5550_hpc.ops = &zt5550_hpc_ops;
	if (!poll) {
		zt5550_hpc.irq = hc_dev->irq;
		zt5550_hpc.irq_flags = IRQF_SHARED;
		zt5550_hpc.dev_id = hc_dev;

		zt5550_hpc_ops.enable_irq = zt5550_hc_enable_irq;
		zt5550_hpc_ops.disable_irq = zt5550_hc_disable_irq;
		zt5550_hpc_ops.check_irq = zt5550_hc_check_irq;
	} else {
		info("using ENUM# polling mode");
	}

	status = cpci_hp_register_controller(&zt5550_hpc);
	if (status != 0) {
		err("could not register cPCI hotplug controller");
		goto init_hc_error;
	}
	dbg("registered controller");

	/* Look for first device matching cPCI bus's bridge vendor and device IDs */
	bus0_dev = pci_get_device(PCI_VENDOR_ID_DEC,
				  PCI_DEVICE_ID_DEC_21154, NULL);
	if (!bus0_dev) {
		status = -ENODEV;
		goto init_register_error;
	}
	bus0 = bus0_dev->subordinate;
	pci_dev_put(bus0_dev);

	status = cpci_hp_register_bus(bus0, 0x0a, 0x0f);
	if (status != 0) {
		err("could not register cPCI hotplug bus");
		goto init_register_error;
	}
	dbg("registered bus");

	status = cpci_hp_start();
	if (status != 0) {
		err("could not started cPCI hotplug system");
		cpci_hp_unregister_bus(bus0);
		goto init_register_error;
	}
	dbg("started cpci hp system");

	return 0;
init_register_error:
	cpci_hp_unregister_controller(&zt5550_hpc);
init_hc_error:
	err("status = %d", status);
	zt5550_hc_cleanup();
	return status;

}