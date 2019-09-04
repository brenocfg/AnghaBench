#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct amd_northbridge {int dummy; } ;
struct TYPE_6__ {scalar_t__ num; int /*<<< orphan*/  flags; struct amd_northbridge* nb; } ;
struct TYPE_5__ {int x86; int x86_model; int x86_stepping; } ;
struct TYPE_4__ {struct pci_dev* link; struct pci_dev* misc; struct pci_dev* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_NB_GART ; 
 int /*<<< orphan*/  AMD_NB_L3_INDEX_DISABLE ; 
 int /*<<< orphan*/  AMD_NB_L3_PARTITIONING ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ amd_gart_present () ; 
 int /*<<< orphan*/  amd_nb_link_ids ; 
 int /*<<< orphan*/  amd_nb_misc_ids ; 
 TYPE_3__ amd_northbridges ; 
 int /*<<< orphan*/  amd_root_ids ; 
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid_edx (int) ; 
 struct amd_northbridge* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct pci_dev* next_northbridge (struct pci_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__* node_to_amd_nb (scalar_t__) ; 

int amd_cache_northbridges(void)
{
	u16 i = 0;
	struct amd_northbridge *nb;
	struct pci_dev *root, *misc, *link;

	if (amd_northbridges.num)
		return 0;

	misc = NULL;
	while ((misc = next_northbridge(misc, amd_nb_misc_ids)) != NULL)
		i++;

	if (!i)
		return -ENODEV;

	nb = kcalloc(i, sizeof(struct amd_northbridge), GFP_KERNEL);
	if (!nb)
		return -ENOMEM;

	amd_northbridges.nb = nb;
	amd_northbridges.num = i;

	link = misc = root = NULL;
	for (i = 0; i != amd_northbridges.num; i++) {
		node_to_amd_nb(i)->root = root =
			next_northbridge(root, amd_root_ids);
		node_to_amd_nb(i)->misc = misc =
			next_northbridge(misc, amd_nb_misc_ids);
		node_to_amd_nb(i)->link = link =
			next_northbridge(link, amd_nb_link_ids);
	}

	if (amd_gart_present())
		amd_northbridges.flags |= AMD_NB_GART;

	/*
	 * Check for L3 cache presence.
	 */
	if (!cpuid_edx(0x80000006))
		return 0;

	/*
	 * Some CPU families support L3 Cache Index Disable. There are some
	 * limitations because of E382 and E388 on family 0x10.
	 */
	if (boot_cpu_data.x86 == 0x10 &&
	    boot_cpu_data.x86_model >= 0x8 &&
	    (boot_cpu_data.x86_model > 0x9 ||
	     boot_cpu_data.x86_stepping >= 0x1))
		amd_northbridges.flags |= AMD_NB_L3_INDEX_DISABLE;

	if (boot_cpu_data.x86 == 0x15)
		amd_northbridges.flags |= AMD_NB_L3_INDEX_DISABLE;

	/* L3 cache partitioning is supported on family 0x15 */
	if (boot_cpu_data.x86 == 0x15)
		amd_northbridges.flags |= AMD_NB_L3_PARTITIONING;

	return 0;
}