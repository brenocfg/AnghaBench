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
struct TYPE_2__ {scalar_t__ pmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_PCK ; 
 scalar_t__ AT91_PMC_SCDR ; 
 TYPE_1__ pm_data ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void at91rm9200_idle(void)
{
	/*
	 * Disable the processor clock.  The processor will be automatically
	 * re-enabled by an interrupt or by a reset.
	 */
	writel(AT91_PMC_PCK, pm_data.pmc + AT91_PMC_SCDR);
}