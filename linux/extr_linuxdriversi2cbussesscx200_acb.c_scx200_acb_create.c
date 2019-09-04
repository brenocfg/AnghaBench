#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct i2c_adapter {TYPE_1__ dev; } ;
struct scx200_acb_iface {struct scx200_acb_iface* next; struct i2c_adapter adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct scx200_acb_iface* scx200_acb_list ; 
 int /*<<< orphan*/  scx200_acb_list_mutex ; 
 int scx200_acb_probe (struct scx200_acb_iface*) ; 
 int /*<<< orphan*/  scx200_acb_reset (struct scx200_acb_iface*) ; 

__attribute__((used)) static int scx200_acb_create(struct scx200_acb_iface *iface)
{
	struct i2c_adapter *adapter;
	int rc;

	adapter = &iface->adapter;

	rc = scx200_acb_probe(iface);
	if (rc) {
		pr_warn("probe failed\n");
		return rc;
	}

	scx200_acb_reset(iface);

	if (i2c_add_adapter(adapter) < 0) {
		pr_err("failed to register\n");
		return -ENODEV;
	}

	if (!adapter->dev.parent) {
		/* If there's no dev, we're tracking (ISA) ifaces manually */
		mutex_lock(&scx200_acb_list_mutex);
		iface->next = scx200_acb_list;
		scx200_acb_list = iface;
		mutex_unlock(&scx200_acb_list_mutex);
	}

	return 0;
}