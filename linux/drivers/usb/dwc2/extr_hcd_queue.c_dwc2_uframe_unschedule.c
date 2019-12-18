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
struct dwc2_qh {int num_hs_transfers; scalar_t__ schedule_low_speed; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_hs_pmap_unschedule (struct dwc2_hsotg*,struct dwc2_qh*,int) ; 
 int /*<<< orphan*/  dwc2_ls_pmap_unschedule (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_sch_dbg (struct dwc2_hsotg*,char*,struct dwc2_qh*) ; 

__attribute__((used)) static void dwc2_uframe_unschedule(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	int i;

	for (i = 0; i < qh->num_hs_transfers; i++)
		dwc2_hs_pmap_unschedule(hsotg, qh, i);

	if (qh->schedule_low_speed)
		dwc2_ls_pmap_unschedule(hsotg, qh);

	dwc2_sch_dbg(hsotg, "QH=%p Unscheduled\n", qh);
}