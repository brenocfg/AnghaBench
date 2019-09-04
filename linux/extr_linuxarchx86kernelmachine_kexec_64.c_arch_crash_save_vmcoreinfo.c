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

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_IMAGE_SIZE ; 
 int /*<<< orphan*/  VMCOREINFO_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_SYMBOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_top_pgt ; 
 int /*<<< orphan*/  kaslr_offset () ; 
 int /*<<< orphan*/  pgtable_l5_enabled () ; 
 int /*<<< orphan*/  phys_base ; 
 int /*<<< orphan*/  vmcoreinfo_append_str (char*,int /*<<< orphan*/ ) ; 

void arch_crash_save_vmcoreinfo(void)
{
	VMCOREINFO_NUMBER(phys_base);
	VMCOREINFO_SYMBOL(init_top_pgt);
	vmcoreinfo_append_str("NUMBER(pgtable_l5_enabled)=%d\n",
			pgtable_l5_enabled());

#ifdef CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#endif
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n",
			      kaslr_offset());
	VMCOREINFO_NUMBER(KERNEL_IMAGE_SIZE);
}