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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct ocxl_fn {int /*<<< orphan*/  afu_list; } ;
struct ocxl_afu {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int activate_afu (struct pci_dev*,struct ocxl_afu*) ; 
 struct ocxl_afu* alloc_afu (struct ocxl_fn*) ; 
 int configure_afu (struct ocxl_afu*,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  deconfigure_afu (struct ocxl_afu*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocxl_afu_put (struct ocxl_afu*) ; 

__attribute__((used)) static int init_afu(struct pci_dev *dev, struct ocxl_fn *fn, u8 afu_idx)
{
	int rc;
	struct ocxl_afu *afu;

	afu = alloc_afu(fn);
	if (!afu)
		return -ENOMEM;

	rc = configure_afu(afu, afu_idx, dev);
	if (rc) {
		ocxl_afu_put(afu);
		return rc;
	}

	rc = activate_afu(dev, afu);
	if (rc) {
		deconfigure_afu(afu);
		ocxl_afu_put(afu);
		return rc;
	}

	list_add_tail(&afu->list, &fn->afu_list);

	return 0;
}