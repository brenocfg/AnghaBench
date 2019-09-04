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
struct pci_dev {int dummy; } ;
struct ddb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddb_buffers_free (struct ddb*) ; 
 int /*<<< orphan*/  ddb_device_destroy (struct ddb*) ; 
 int /*<<< orphan*/  ddb_i2c_release (struct ddb*) ; 
 int /*<<< orphan*/  ddb_irq_exit (struct ddb*) ; 
 int /*<<< orphan*/  ddb_msi_exit (struct ddb*) ; 
 int /*<<< orphan*/  ddb_ports_detach (struct ddb*) ; 
 int /*<<< orphan*/  ddb_ports_release (struct ddb*) ; 
 int /*<<< orphan*/  ddb_unmap (struct ddb*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddb_remove(struct pci_dev *pdev)
{
	struct ddb *dev = (struct ddb *)pci_get_drvdata(pdev);

	ddb_device_destroy(dev);
	ddb_ports_detach(dev);
	ddb_i2c_release(dev);

	ddb_irq_exit(dev);
	ddb_msi_exit(dev);
	ddb_ports_release(dev);
	ddb_buffers_free(dev);

	ddb_unmap(dev);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
}