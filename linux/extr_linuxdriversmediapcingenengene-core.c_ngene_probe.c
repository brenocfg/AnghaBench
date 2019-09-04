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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ngene_info {int /*<<< orphan*/  name; } ;
struct ngene {int i2c_current_bus; struct ngene_info* card_info; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cxd_attach (struct ngene*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int init_channels (struct ngene*) ; 
 int ngene_buffer_config (struct ngene*) ; 
 int ngene_get_buffers (struct ngene*) ; 
 int /*<<< orphan*/  ngene_release_buffers (struct ngene*) ; 
 int ngene_start (struct ngene*) ; 
 int /*<<< orphan*/  ngene_stop (struct ngene*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ngene*) ; 
 struct ngene* vzalloc (int) ; 

int ngene_probe(struct pci_dev *pci_dev, const struct pci_device_id *id)
{
	struct ngene *dev;
	int stat = 0;

	if (pci_enable_device(pci_dev) < 0)
		return -ENODEV;

	dev = vzalloc(sizeof(struct ngene));
	if (dev == NULL) {
		stat = -ENOMEM;
		goto fail0;
	}

	dev->pci_dev = pci_dev;
	dev->card_info = (struct ngene_info *)id->driver_data;
	dev_info(&pci_dev->dev, "Found %s\n", dev->card_info->name);

	pci_set_drvdata(pci_dev, dev);

	/* Alloc buffers and start nGene */
	stat = ngene_get_buffers(dev);
	if (stat < 0)
		goto fail1;
	stat = ngene_start(dev);
	if (stat < 0)
		goto fail1;

	cxd_attach(dev);

	stat = ngene_buffer_config(dev);
	if (stat < 0)
		goto fail1;


	dev->i2c_current_bus = -1;

	/* Register DVB adapters and devices for both channels */
	stat = init_channels(dev);
	if (stat < 0)
		goto fail2;

	return 0;

fail2:
	ngene_stop(dev);
fail1:
	ngene_release_buffers(dev);
fail0:
	pci_disable_device(pci_dev);
	return stat;
}