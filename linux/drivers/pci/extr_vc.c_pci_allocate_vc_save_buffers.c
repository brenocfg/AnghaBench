#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ pci_add_ext_cap_save_buffer (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_vc_do_save_buffer (struct pci_dev*,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* vc_caps ; 

void pci_allocate_vc_save_buffers(struct pci_dev *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vc_caps); i++) {
		int len, pos = pci_find_ext_capability(dev, vc_caps[i].id);

		if (!pos)
			continue;

		len = pci_vc_do_save_buffer(dev, pos, NULL, false);
		if (pci_add_ext_cap_save_buffer(dev, vc_caps[i].id, len))
			pci_err(dev, "unable to preallocate %s save buffer\n",
				vc_caps[i].name);
	}
}