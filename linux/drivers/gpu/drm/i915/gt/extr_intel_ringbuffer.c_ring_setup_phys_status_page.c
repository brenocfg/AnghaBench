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
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFN_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hws_pga (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hwstam (struct intel_engine_cs*,unsigned int) ; 
 int /*<<< orphan*/  status_page (struct intel_engine_cs*) ; 

__attribute__((used)) static void ring_setup_phys_status_page(struct intel_engine_cs *engine)
{
	set_hws_pga(engine, PFN_PHYS(page_to_pfn(status_page(engine))));
	set_hwstam(engine, ~0u);
}