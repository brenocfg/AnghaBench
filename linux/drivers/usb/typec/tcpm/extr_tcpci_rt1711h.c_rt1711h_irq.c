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
typedef  int u8 ;
typedef  int u16 ;
struct rt1711h_chip {int /*<<< orphan*/  tcpci; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TCPC_ALERT ; 
 int TCPC_ALERT_CC_STATUS ; 
 int /*<<< orphan*/  TCPC_CC_STATUS ; 
 int TCPC_CC_STATUS_TOGGLING ; 
 int rt1711h_read16 (struct rt1711h_chip*,int /*<<< orphan*/ ,int*) ; 
 int rt1711h_read8 (struct rt1711h_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt1711h_write8 (struct rt1711h_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcpci_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rt1711h_irq(int irq, void *dev_id)
{
	int ret;
	u16 alert;
	u8 status;
	struct rt1711h_chip *chip = dev_id;

	if (!chip->tcpci)
		return IRQ_HANDLED;

	ret = rt1711h_read16(chip, TCPC_ALERT, &alert);
	if (ret < 0)
		goto out;

	if (alert & TCPC_ALERT_CC_STATUS) {
		ret = rt1711h_read8(chip, TCPC_CC_STATUS, &status);
		if (ret < 0)
			goto out;
		/* Clear cc change event triggered by starting toggling */
		if (status & TCPC_CC_STATUS_TOGGLING)
			rt1711h_write8(chip, TCPC_ALERT, TCPC_ALERT_CC_STATUS);
	}

out:
	return tcpci_irq(chip->tcpci);
}