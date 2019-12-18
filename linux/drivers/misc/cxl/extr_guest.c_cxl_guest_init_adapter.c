#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct cxl_guest {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct cxl {int psl_timebase_synced; TYPE_2__ dev; TYPE_1__* guest; scalar_t__ slices; } ;
struct TYPE_3__ {struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cxl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cxl_adapter_context_unlock (struct cxl*) ; 
 struct cxl* cxl_alloc_adapter () ; 
 int cxl_guest_add_chardev (struct cxl*) ; 
 int /*<<< orphan*/  cxl_guest_remove_chardev (struct cxl*) ; 
 int cxl_of_read_adapter_handle (struct cxl*,struct device_node*) ; 
 int cxl_of_read_adapter_properties (struct cxl*,struct device_node*) ; 
 int cxl_register_adapter (struct cxl*) ; 
 int cxl_sysfs_adapter_add (struct cxl*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct cxl*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  free_adapter (struct cxl*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int properties_look_ok (struct cxl*) ; 
 int /*<<< orphan*/  release_adapter ; 

struct cxl *cxl_guest_init_adapter(struct device_node *np, struct platform_device *pdev)
{
	struct cxl *adapter;
	bool free = true;
	int rc;

	if (!(adapter = cxl_alloc_adapter()))
		return ERR_PTR(-ENOMEM);

	if (!(adapter->guest = kzalloc(sizeof(struct cxl_guest), GFP_KERNEL))) {
		free_adapter(adapter);
		return ERR_PTR(-ENOMEM);
	}

	adapter->slices = 0;
	adapter->guest->pdev = pdev;
	adapter->dev.parent = &pdev->dev;
	adapter->dev.release = release_adapter;
	dev_set_drvdata(&pdev->dev, adapter);

	/*
	 * Hypervisor controls PSL timebase initialization (p1 register).
	 * On FW840, PSL is initialized.
	 */
	adapter->psl_timebase_synced = true;

	if ((rc = cxl_of_read_adapter_handle(adapter, np)))
		goto err1;

	if ((rc = cxl_of_read_adapter_properties(adapter, np)))
		goto err1;

	if ((rc = properties_look_ok(adapter)))
		goto err1;

	if ((rc = cxl_guest_add_chardev(adapter)))
		goto err1;

	/*
	 * After we call this function we must not free the adapter directly,
	 * even if it returns an error!
	 */
	if ((rc = cxl_register_adapter(adapter)))
		goto err_put1;

	if ((rc = cxl_sysfs_adapter_add(adapter)))
		goto err_put1;

	/* release the context lock as the adapter is configured */
	cxl_adapter_context_unlock(adapter);

	return adapter;

err_put1:
	device_unregister(&adapter->dev);
	free = false;
	cxl_guest_remove_chardev(adapter);
err1:
	if (free)
		free_adapter(adapter);
	return ERR_PTR(rc);
}