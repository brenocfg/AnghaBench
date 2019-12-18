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
typedef  int u64 ;
struct qib_pportdata {int dummy; } ;
struct qib_devdata {struct qib_pportdata* pport; } ;

/* Variables and functions */
 int INT_MASK_P (int /*<<< orphan*/ ,int) ; 
 int INT_MASK_PM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDma ; 
 int /*<<< orphan*/  SDmaCleanupDone ; 
 int /*<<< orphan*/  SDmaIdle ; 
 int /*<<< orphan*/  SDmaProgress ; 
 int /*<<< orphan*/  qib_sdma_event_e20_hw_started ; 
 int /*<<< orphan*/  qib_sdma_intr (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_7322_intr(struct qib_devdata *dd, u64 istat)
{
	struct qib_pportdata *ppd0 = &dd->pport[0];
	struct qib_pportdata *ppd1 = &dd->pport[1];
	u64 intr0 = istat & (INT_MASK_P(SDma, 0) |
		INT_MASK_P(SDmaIdle, 0) | INT_MASK_P(SDmaProgress, 0));
	u64 intr1 = istat & (INT_MASK_P(SDma, 1) |
		INT_MASK_P(SDmaIdle, 1) | INT_MASK_P(SDmaProgress, 1));

	if (intr0)
		qib_sdma_intr(ppd0);
	if (intr1)
		qib_sdma_intr(ppd1);

	if (istat & INT_MASK_PM(SDmaCleanupDone, 0))
		qib_sdma_process_event(ppd0, qib_sdma_event_e20_hw_started);
	if (istat & INT_MASK_PM(SDmaCleanupDone, 1))
		qib_sdma_process_event(ppd1, qib_sdma_event_e20_hw_started);
}