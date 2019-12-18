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
struct msm_edp {int /*<<< orphan*/  ctrl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  msm_edp_ctrl_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t edp_irq(int irq, void *dev_id)
{
	struct msm_edp *edp = dev_id;

	/* Process eDP irq */
	return msm_edp_ctrl_irq(edp->ctrl);
}