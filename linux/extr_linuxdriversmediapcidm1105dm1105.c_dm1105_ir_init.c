#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int version; int /*<<< orphan*/  product; scalar_t__ vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {char* device_name; TYPE_2__ dev; TYPE_1__ input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; } ;
struct TYPE_7__ {struct rc_dev* dev; int /*<<< orphan*/  work; int /*<<< orphan*/  input_phys; } ;
struct dm1105_dev {TYPE_3__ ir; TYPE_4__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; scalar_t__ vendor; int /*<<< orphan*/  subsystem_device; scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PCI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  RC_DRIVER_SCANCODE ; 
 int /*<<< orphan*/  RC_MAP_DM1105_NEC ; 
 int /*<<< orphan*/  dm1105_emit_key ; 
 char* pci_name (TYPE_4__*) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int dm1105_ir_init(struct dm1105_dev *dm1105)
{
	struct rc_dev *dev;
	int err = -ENOMEM;

	dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	if (!dev)
		return -ENOMEM;

	snprintf(dm1105->ir.input_phys, sizeof(dm1105->ir.input_phys),
		"pci-%s/ir0", pci_name(dm1105->pdev));

	dev->driver_name = MODULE_NAME;
	dev->map_name = RC_MAP_DM1105_NEC;
	dev->device_name = "DVB on-card IR receiver";
	dev->input_phys = dm1105->ir.input_phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.version = 1;
	if (dm1105->pdev->subsystem_vendor) {
		dev->input_id.vendor = dm1105->pdev->subsystem_vendor;
		dev->input_id.product = dm1105->pdev->subsystem_device;
	} else {
		dev->input_id.vendor = dm1105->pdev->vendor;
		dev->input_id.product = dm1105->pdev->device;
	}
	dev->dev.parent = &dm1105->pdev->dev;

	INIT_WORK(&dm1105->ir.work, dm1105_emit_key);

	err = rc_register_device(dev);
	if (err < 0) {
		rc_free_device(dev);
		return err;
	}

	dm1105->ir.dev = dev;
	return 0;
}