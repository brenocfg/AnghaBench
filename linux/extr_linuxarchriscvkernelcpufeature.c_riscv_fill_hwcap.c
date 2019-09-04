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
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned long COMPAT_HWCAP_ISA_A ; 
 unsigned long COMPAT_HWCAP_ISA_C ; 
 unsigned long COMPAT_HWCAP_ISA_D ; 
 unsigned long COMPAT_HWCAP_ISA_F ; 
 unsigned long COMPAT_HWCAP_ISA_I ; 
 unsigned long COMPAT_HWCAP_ISA_M ; 
 unsigned long elf_hwcap ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 size_t strlen (char const*) ; 

void riscv_fill_hwcap(void)
{
	struct device_node *node;
	const char *isa;
	size_t i;
	static unsigned long isa2hwcap[256] = {0};

	isa2hwcap['i'] = isa2hwcap['I'] = COMPAT_HWCAP_ISA_I;
	isa2hwcap['m'] = isa2hwcap['M'] = COMPAT_HWCAP_ISA_M;
	isa2hwcap['a'] = isa2hwcap['A'] = COMPAT_HWCAP_ISA_A;
	isa2hwcap['f'] = isa2hwcap['F'] = COMPAT_HWCAP_ISA_F;
	isa2hwcap['d'] = isa2hwcap['D'] = COMPAT_HWCAP_ISA_D;
	isa2hwcap['c'] = isa2hwcap['C'] = COMPAT_HWCAP_ISA_C;

	elf_hwcap = 0;

	/*
	 * We don't support running Linux on hertergenous ISA systems.  For
	 * now, we just check the ISA of the first processor.
	 */
	node = of_find_node_by_type(NULL, "cpu");
	if (!node) {
		pr_warning("Unable to find \"cpu\" devicetree entry");
		return;
	}

	if (of_property_read_string(node, "riscv,isa", &isa)) {
		pr_warning("Unable to find \"riscv,isa\" devicetree entry");
		return;
	}

	for (i = 0; i < strlen(isa); ++i)
		elf_hwcap |= isa2hwcap[(unsigned char)(isa[i])];

	pr_info("elf_hwcap is 0x%lx", elf_hwcap);
}