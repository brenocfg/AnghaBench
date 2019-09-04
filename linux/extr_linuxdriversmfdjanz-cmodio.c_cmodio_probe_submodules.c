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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct cmodio_device {int /*<<< orphan*/  cells; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cmodio_setup_subdevice (struct cmodio_device*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char** modules ; 
 int num_modules ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int cmodio_probe_submodules(struct cmodio_device *priv)
{
	struct pci_dev *pdev = priv->pdev;
	unsigned int num_probed = 0;
	char *name;
	int i;

	for (i = 0; i < num_modules; i++) {
		name = modules[i];
		if (!strcmp(name, "") || !strcmp(name, "empty"))
			continue;

		dev_dbg(&priv->pdev->dev, "MODULbus %d: name %s\n", i, name);
		cmodio_setup_subdevice(priv, name, num_probed, i);
		num_probed++;
	}

	/* print an error message if no modules were probed */
	if (num_probed == 0) {
		dev_err(&priv->pdev->dev, "no MODULbus modules specified, "
					  "please set the ``modules'' kernel "
					  "parameter according to your "
					  "hardware configuration\n");
		return -ENODEV;
	}

	return mfd_add_devices(&pdev->dev, 0, priv->cells,
			       num_probed, NULL, pdev->irq, NULL);
}