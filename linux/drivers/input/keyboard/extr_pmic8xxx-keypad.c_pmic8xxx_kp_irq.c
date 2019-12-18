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
struct pmic8xxx_kp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEYP_CTRL ; 
 unsigned int KEYP_CTRL_EVNTS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pmic8xxx_kp_scan_matrix (struct pmic8xxx_kp*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t pmic8xxx_kp_irq(int irq, void *data)
{
	struct pmic8xxx_kp *kp = data;
	unsigned int ctrl_val, events;
	int rc;

	rc = regmap_read(kp->regmap, KEYP_CTRL, &ctrl_val);
	if (rc < 0) {
		dev_err(kp->dev, "failed to read keyp_ctrl register\n");
		return IRQ_HANDLED;
	}

	events = ctrl_val & KEYP_CTRL_EVNTS_MASK;

	rc = pmic8xxx_kp_scan_matrix(kp, events);
	if (rc < 0)
		dev_err(kp->dev, "failed to scan matrix\n");

	return IRQ_HANDLED;
}