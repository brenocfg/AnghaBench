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
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct ata_port {int /*<<< orphan*/  print_id; } ;
struct ata_link {int /*<<< orphan*/  pmp; int /*<<< orphan*/  tdev; struct ata_port* ap; } ;
struct ata_device {int /*<<< orphan*/  devno; struct ata_link* link; struct device tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_bind_dev (struct ata_device*) ; 
 scalar_t__ ata_is_host_link (struct ata_link*) ; 
 int /*<<< orphan*/  ata_tdev_free (struct ata_device*) ; 
 int /*<<< orphan*/  ata_tdev_release ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  transport_add_device (struct device*) ; 
 int /*<<< orphan*/  transport_configure_device (struct device*) ; 
 int /*<<< orphan*/  transport_setup_device (struct device*) ; 

__attribute__((used)) static int ata_tdev_add(struct ata_device *ata_dev)
{
	struct device *dev = &ata_dev->tdev;
	struct ata_link *link = ata_dev->link;
	struct ata_port *ap = link->ap;
	int error;

	device_initialize(dev);
	dev->parent = &link->tdev;
	dev->release = ata_tdev_release;
	if (ata_is_host_link(link))
		dev_set_name(dev, "dev%d.%d", ap->print_id,ata_dev->devno);
        else
		dev_set_name(dev, "dev%d.%d.0", ap->print_id, link->pmp);

	transport_setup_device(dev);
	ata_acpi_bind_dev(ata_dev);
	error = device_add(dev);
	if (error) {
		ata_tdev_free(ata_dev);
		return error;
	}

	transport_add_device(dev);
	transport_configure_device(dev);
	return 0;
}