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
typedef  int /*<<< orphan*/  u16 ;
struct pmic8xxx_kp {int /*<<< orphan*/  stuckstate; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PM8XXX_MAX_ROWS ; 
 int /*<<< orphan*/  __pmic8xxx_kp_scan_matrix (struct pmic8xxx_kp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pmic8xxx_kp_read_matrix (struct pmic8xxx_kp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pmic8xxx_kp_stuck_irq(int irq, void *data)
{
	u16 new_state[PM8XXX_MAX_ROWS];
	u16 old_state[PM8XXX_MAX_ROWS];
	int rc;
	struct pmic8xxx_kp *kp = data;

	rc = pmic8xxx_kp_read_matrix(kp, new_state, old_state);
	if (rc < 0) {
		dev_err(kp->dev, "failed to read keypad matrix\n");
		return IRQ_HANDLED;
	}

	__pmic8xxx_kp_scan_matrix(kp, new_state, kp->stuckstate);

	return IRQ_HANDLED;
}