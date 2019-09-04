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
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_all () ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  wbinvd () ; 

__attribute__((used)) static void __cpa_flush_all(void *arg)
{
	unsigned long cache = (unsigned long)arg;

	/*
	 * Flush all to work around Errata in early athlons regarding
	 * large page flushing.
	 */
	__flush_tlb_all();

	if (cache && boot_cpu_data.x86 >= 4)
		wbinvd();
}