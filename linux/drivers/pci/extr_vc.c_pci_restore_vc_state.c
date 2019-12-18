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
struct pci_cap_saved_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_cap_saved_state* pci_find_saved_ext_cap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_vc_do_save_buffer (struct pci_dev*,int,struct pci_cap_saved_state*,int) ; 
 TYPE_1__* vc_caps ; 

void pci_restore_vc_state(struct pci_dev *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vc_caps); i++) {
		int pos;
		struct pci_cap_saved_state *save_state;

		pos = pci_find_ext_capability(dev, vc_caps[i].id);
		save_state = pci_find_saved_ext_cap(dev, vc_caps[i].id);
		if (!save_state || !pos)
			continue;

		pci_vc_do_save_buffer(dev, pos, save_state, false);
	}
}