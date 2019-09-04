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
struct cxl_native {int dummy; } ;
struct cxl {int perst_loads_image; int perst_same_image; int /*<<< orphan*/  dev; int /*<<< orphan*/  native; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cxl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cxl_adapter_context_unlock (struct cxl*) ; 
 struct cxl* cxl_alloc_adapter () ; 
 int cxl_configure_adapter (struct cxl*,struct pci_dev*) ; 
 int /*<<< orphan*/  cxl_debugfs_adapter_add (struct cxl*) ; 
 int /*<<< orphan*/  cxl_debugfs_adapter_remove (struct cxl*) ; 
 int /*<<< orphan*/  cxl_deconfigure_adapter (struct cxl*) ; 
 int cxl_register_adapter (struct cxl*) ; 
 int /*<<< orphan*/  cxl_release_adapter (int /*<<< orphan*/ *) ; 
 int cxl_sysfs_adapter_add (struct cxl*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  set_sl_ops (struct cxl*,struct pci_dev*) ; 

__attribute__((used)) static struct cxl *cxl_pci_init_adapter(struct pci_dev *dev)
{
	struct cxl *adapter;
	int rc;

	adapter = cxl_alloc_adapter();
	if (!adapter)
		return ERR_PTR(-ENOMEM);

	adapter->native = kzalloc(sizeof(struct cxl_native), GFP_KERNEL);
	if (!adapter->native) {
		rc = -ENOMEM;
		goto err_release;
	}

	set_sl_ops(adapter, dev);

	/* Set defaults for parameters which need to persist over
	 * configure/reconfigure
	 */
	adapter->perst_loads_image = true;
	adapter->perst_same_image = false;

	rc = cxl_configure_adapter(adapter, dev);
	if (rc) {
		pci_disable_device(dev);
		goto err_release;
	}

	/* Don't care if this one fails: */
	cxl_debugfs_adapter_add(adapter);

	/*
	 * After we call this function we must not free the adapter directly,
	 * even if it returns an error!
	 */
	if ((rc = cxl_register_adapter(adapter)))
		goto err_put1;

	if ((rc = cxl_sysfs_adapter_add(adapter)))
		goto err_put1;

	/* Release the context lock as adapter is configured */
	cxl_adapter_context_unlock(adapter);

	return adapter;

err_put1:
	/* This should mirror cxl_remove_adapter, except without the
	 * sysfs parts
	 */
	cxl_debugfs_adapter_remove(adapter);
	cxl_deconfigure_adapter(adapter);
	device_unregister(&adapter->dev);
	return ERR_PTR(rc);

err_release:
	cxl_release_adapter(&adapter->dev);
	return ERR_PTR(rc);
}