#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuinfo_x86 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* c_detect_tlb ) (struct cpuinfo_x86*) ;} ;

/* Variables and functions */
 size_t ENTRIES ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (struct cpuinfo_x86*) ; 
 TYPE_1__* this_cpu ; 
 int /*<<< orphan*/ * tlb_lld_1g ; 
 int /*<<< orphan*/ * tlb_lld_2m ; 
 int /*<<< orphan*/ * tlb_lld_4k ; 
 int /*<<< orphan*/ * tlb_lld_4m ; 
 int /*<<< orphan*/ * tlb_lli_2m ; 
 int /*<<< orphan*/ * tlb_lli_4k ; 
 int /*<<< orphan*/ * tlb_lli_4m ; 

__attribute__((used)) static void cpu_detect_tlb(struct cpuinfo_x86 *c)
{
	if (this_cpu->c_detect_tlb)
		this_cpu->c_detect_tlb(c);

	pr_info("Last level iTLB entries: 4KB %d, 2MB %d, 4MB %d\n",
		tlb_lli_4k[ENTRIES], tlb_lli_2m[ENTRIES],
		tlb_lli_4m[ENTRIES]);

	pr_info("Last level dTLB entries: 4KB %d, 2MB %d, 4MB %d, 1GB %d\n",
		tlb_lld_4k[ENTRIES], tlb_lld_2m[ENTRIES],
		tlb_lld_4m[ENTRIES], tlb_lld_1g[ENTRIES]);
}