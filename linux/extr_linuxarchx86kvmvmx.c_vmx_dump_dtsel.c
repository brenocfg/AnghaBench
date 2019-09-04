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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ GUEST_GDTR_BASE ; 
 scalar_t__ GUEST_GDTR_LIMIT ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_read32 (scalar_t__) ; 
 int /*<<< orphan*/  vmcs_readl (scalar_t__) ; 

__attribute__((used)) static void vmx_dump_dtsel(char *name, uint32_t limit)
{
	pr_err("%s                           limit=0x%08x, base=0x%016lx\n",
	       name, vmcs_read32(limit),
	       vmcs_readl(limit + GUEST_GDTR_BASE - GUEST_GDTR_LIMIT));
}