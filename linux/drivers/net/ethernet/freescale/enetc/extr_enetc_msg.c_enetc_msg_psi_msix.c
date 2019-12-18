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
struct enetc_si {int /*<<< orphan*/  hw; } ;
struct enetc_pf {int /*<<< orphan*/  msg_task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  enetc_msg_disable_mr_int (int /*<<< orphan*/ *) ; 
 struct enetc_pf* enetc_si_priv (struct enetc_si*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t enetc_msg_psi_msix(int irq, void *data)
{
	struct enetc_si *si = (struct enetc_si *)data;
	struct enetc_pf *pf = enetc_si_priv(si);

	enetc_msg_disable_mr_int(&si->hw);
	schedule_work(&pf->msg_task);

	return IRQ_HANDLED;
}