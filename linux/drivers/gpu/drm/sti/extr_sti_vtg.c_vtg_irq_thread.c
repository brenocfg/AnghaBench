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
typedef  int /*<<< orphan*/  u32 ;
struct sti_vtg {int irq_status; int /*<<< orphan*/  crtc; int /*<<< orphan*/  notifier_list; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  VTG_BOTTOM_FIELD_EVENT ; 
 int VTG_IRQ_TOP ; 
 int /*<<< orphan*/  VTG_TOP_FIELD_EVENT ; 
 int /*<<< orphan*/  raw_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vtg_irq_thread(int irq, void *arg)
{
	struct sti_vtg *vtg = arg;
	u32 event;

	event = (vtg->irq_status & VTG_IRQ_TOP) ?
		VTG_TOP_FIELD_EVENT : VTG_BOTTOM_FIELD_EVENT;

	raw_notifier_call_chain(&vtg->notifier_list, event, vtg->crtc);

	return IRQ_HANDLED;
}