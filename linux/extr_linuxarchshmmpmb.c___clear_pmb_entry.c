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
struct pmb_entry {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 unsigned long PMB_V ; 
 unsigned long __raw_readl (unsigned long) ; 
 unsigned long mk_pmb_addr (int /*<<< orphan*/ ) ; 
 unsigned long mk_pmb_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_uncached (unsigned long,unsigned long) ; 

__attribute__((used)) static void __clear_pmb_entry(struct pmb_entry *pmbe)
{
	unsigned long addr, data;
	unsigned long addr_val, data_val;

	addr = mk_pmb_addr(pmbe->entry);
	data = mk_pmb_data(pmbe->entry);

	addr_val = __raw_readl(addr);
	data_val = __raw_readl(data);

	/* Clear V-bit */
	writel_uncached(addr_val & ~PMB_V, addr);
	writel_uncached(data_val & ~PMB_V, data);
}