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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 TYPE_2__ ali1563_adapter ; 
 int ali1563_setup (struct pci_dev*) ; 
 int /*<<< orphan*/  ali1563_shutdown (struct pci_dev*) ; 
 int ali1563_smba ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int ali1563_probe(struct pci_dev *dev,
			 const struct pci_device_id *id_table)
{
	int error;

	error = ali1563_setup(dev);
	if (error)
		goto exit;
	ali1563_adapter.dev.parent = &dev->dev;
	snprintf(ali1563_adapter.name, sizeof(ali1563_adapter.name),
		 "SMBus ALi 1563 Adapter @ %04x", ali1563_smba);
	error = i2c_add_adapter(&ali1563_adapter);
	if (error)
		goto exit_shutdown;
	return 0;

exit_shutdown:
	ali1563_shutdown(dev);
exit:
	dev_warn(&dev->dev, "ALi1563 SMBus probe failed (%d)\n", error);
	return error;
}