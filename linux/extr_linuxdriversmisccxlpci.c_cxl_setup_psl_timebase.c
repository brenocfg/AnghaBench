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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct cxl {int psl_timebase_synced; TYPE_2__* native; } ;
struct TYPE_4__ {TYPE_1__* sl_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_timebase_ctrl ) (struct cxl*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_Control ; 
 int CXL_PSL_Control_tb ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* pnv_pci_get_phb_node (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct cxl*) ; 

__attribute__((used)) static void cxl_setup_psl_timebase(struct cxl *adapter, struct pci_dev *dev)
{
	struct device_node *np;

	adapter->psl_timebase_synced = false;

	if (!(np = pnv_pci_get_phb_node(dev)))
		return;

	/* Do not fail when CAPP timebase sync is not supported by OPAL */
	of_node_get(np);
	if (! of_get_property(np, "ibm,capp-timebase-sync", NULL)) {
		of_node_put(np);
		dev_info(&dev->dev, "PSL timebase inactive: OPAL support missing\n");
		return;
	}
	of_node_put(np);

	/*
	 * Setup PSL Timebase Control and Status register
	 * with the recommended Timebase Sync Count value
	 */
	if (adapter->native->sl_ops->write_timebase_ctrl)
		adapter->native->sl_ops->write_timebase_ctrl(adapter);

	/* Enable PSL Timebase */
	cxl_p1_write(adapter, CXL_PSL_Control, 0x0000000000000000);
	cxl_p1_write(adapter, CXL_PSL_Control, CXL_PSL_Control_tb);

	return;
}