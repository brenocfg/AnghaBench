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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SDMA_IDLE_START ; 
 scalar_t__ IS_SDMA_PROGRESS_START ; 
 scalar_t__ IS_SDMA_START ; 
 int /*<<< orphan*/  remap_intr (struct hfi1_devdata*,scalar_t__,int) ; 

void remap_sdma_interrupts(struct hfi1_devdata *dd, int engine, int msix_intr)
{
	/*
	 * SDMA engine interrupt sources grouped by type, rather than
	 * engine.  Per-engine interrupts are as follows:
	 *	SDMA
	 *	SDMAProgress
	 *	SDMAIdle
	 */
	remap_intr(dd, IS_SDMA_START + engine, msix_intr);
	remap_intr(dd, IS_SDMA_PROGRESS_START + engine, msix_intr);
	remap_intr(dd, IS_SDMA_IDLE_START + engine, msix_intr);
}