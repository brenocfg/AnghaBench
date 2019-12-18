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
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_sdma_event_e50_hw_cleaned ; 

__attribute__((used)) static void qib_7322_sdma_hw_clean_up(struct qib_pportdata *ppd)
{
	__qib_sdma_process_event(ppd, qib_sdma_event_e50_hw_cleaned);
}