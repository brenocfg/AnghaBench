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
struct mc13783_pwrb {int flags; int /*<<< orphan*/  pwr; int /*<<< orphan*/ * keymap; int /*<<< orphan*/  mc13783; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MC13783_IRQSENSE1_ONOFD1S ; 
 int MC13783_IRQSENSE1_ONOFD2S ; 
 int MC13783_IRQSENSE1_ONOFD3S ; 
#define  MC13783_IRQ_ONOFD1 130 
#define  MC13783_IRQ_ONOFD2 129 
#define  MC13783_IRQ_ONOFD3 128 
 int MC13783_PWRB_B1_POL_INVERT ; 
 int MC13783_PWRB_B2_POL_INVERT ; 
 int MC13783_PWRB_B3_POL_INVERT ; 
 int /*<<< orphan*/  MC13783_REG_INTERRUPT_SENSE_1 ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_irq_ack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mc13xxx_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t button_irq(int irq, void *_priv)
{
	struct mc13783_pwrb *priv = _priv;
	int val;

	mc13xxx_irq_ack(priv->mc13783, irq);
	mc13xxx_reg_read(priv->mc13783, MC13783_REG_INTERRUPT_SENSE_1, &val);

	switch (irq) {
	case MC13783_IRQ_ONOFD1:
		val = val & MC13783_IRQSENSE1_ONOFD1S ? 1 : 0;
		if (priv->flags & MC13783_PWRB_B1_POL_INVERT)
			val ^= 1;
		input_report_key(priv->pwr, priv->keymap[0], val);
		break;

	case MC13783_IRQ_ONOFD2:
		val = val & MC13783_IRQSENSE1_ONOFD2S ? 1 : 0;
		if (priv->flags & MC13783_PWRB_B2_POL_INVERT)
			val ^= 1;
		input_report_key(priv->pwr, priv->keymap[1], val);
		break;

	case MC13783_IRQ_ONOFD3:
		val = val & MC13783_IRQSENSE1_ONOFD3S ? 1 : 0;
		if (priv->flags & MC13783_PWRB_B3_POL_INVERT)
			val ^= 1;
		input_report_key(priv->pwr, priv->keymap[2], val);
		break;
	}

	input_sync(priv->pwr);

	return IRQ_HANDLED;
}