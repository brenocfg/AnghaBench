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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,struct dentry*) ; 
 struct dentry* nfp_dir ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 

struct dentry *nfp_net_debugfs_device_add(struct pci_dev *pdev)
{
	struct dentry *dev_dir;

	if (IS_ERR_OR_NULL(nfp_dir))
		return NULL;

	dev_dir = debugfs_create_dir(pci_name(pdev), nfp_dir);
	if (IS_ERR_OR_NULL(dev_dir))
		return NULL;

	return dev_dir;
}