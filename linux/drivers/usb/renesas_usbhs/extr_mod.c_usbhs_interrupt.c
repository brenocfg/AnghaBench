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
struct usbhs_priv {int dummy; } ;
struct usbhs_irq_state {int intsts0; int intsts1; int brdysts; int nrdysts; int bempsts; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ATTCH ; 
 int BEMP ; 
 int /*<<< orphan*/  BEMPSTS ; 
 int BRDY ; 
 int /*<<< orphan*/  BRDYSTS ; 
 int CTRT ; 
 int DTCH ; 
 int DVST ; 
 int /*<<< orphan*/  INTSTS0 ; 
 int INTSTS0_MAGIC ; 
 int /*<<< orphan*/  INTSTS1 ; 
 int INTSTS1_MAGIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  NRDYSTS ; 
 int SACK ; 
 int SIGN ; 
 int VBINT ; 
 int /*<<< orphan*/  irq_attch ; 
 int /*<<< orphan*/  irq_ctrl_stage ; 
 int /*<<< orphan*/  irq_dev_state ; 
 int /*<<< orphan*/  irq_dtch ; 
 int /*<<< orphan*/  irq_empty ; 
 int /*<<< orphan*/  irq_ready ; 
 int /*<<< orphan*/  irq_sack ; 
 int /*<<< orphan*/  irq_sign ; 
 int /*<<< orphan*/  irq_vbus ; 
 int /*<<< orphan*/  usbhs_mod_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct usbhs_priv*,struct usbhs_irq_state*) ; 
 int /*<<< orphan*/  usbhs_mod_info_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct usbhs_priv*,struct usbhs_irq_state*) ; 
 scalar_t__ usbhs_mod_is_host (struct usbhs_priv*) ; 
 scalar_t__ usbhs_status_get_each_irq (struct usbhs_priv*,struct usbhs_irq_state*) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t usbhs_interrupt(int irq, void *data)
{
	struct usbhs_priv *priv = data;
	struct usbhs_irq_state irq_state;

	if (usbhs_status_get_each_irq(priv, &irq_state) < 0)
		return IRQ_NONE;

	/*
	 * clear interrupt
	 *
	 * The hardware is _very_ picky to clear interrupt bit.
	 * Especially INTSTS0_MAGIC, INTSTS1_MAGIC value.
	 *
	 * see
	 *	"Operation"
	 *	 - "Control Transfer (DCP)"
	 *	   - Function :: VALID bit should 0
	 */
	usbhs_write(priv, INTSTS0, ~irq_state.intsts0 & INTSTS0_MAGIC);
	if (usbhs_mod_is_host(priv))
		usbhs_write(priv, INTSTS1, ~irq_state.intsts1 & INTSTS1_MAGIC);

	/*
	 * The driver should not clear the xxxSTS after the line of
	 * "call irq callback functions" because each "if" statement is
	 * possible to call the callback function for avoiding any side effects.
	 */
	if (irq_state.intsts0 & BRDY)
		usbhs_write(priv, BRDYSTS, ~irq_state.brdysts);
	usbhs_write(priv, NRDYSTS, ~irq_state.nrdysts);
	if (irq_state.intsts0 & BEMP)
		usbhs_write(priv, BEMPSTS, ~irq_state.bempsts);

	/*
	 * call irq callback functions
	 * see also
	 *	usbhs_irq_setting_update
	 */

	/* INTSTS0 */
	if (irq_state.intsts0 & VBINT)
		usbhs_mod_info_call(priv, irq_vbus, priv, &irq_state);

	if (irq_state.intsts0 & DVST)
		usbhs_mod_call(priv, irq_dev_state, priv, &irq_state);

	if (irq_state.intsts0 & CTRT)
		usbhs_mod_call(priv, irq_ctrl_stage, priv, &irq_state);

	if (irq_state.intsts0 & BEMP)
		usbhs_mod_call(priv, irq_empty, priv, &irq_state);

	if (irq_state.intsts0 & BRDY)
		usbhs_mod_call(priv, irq_ready, priv, &irq_state);

	if (usbhs_mod_is_host(priv)) {
		/* INTSTS1 */
		if (irq_state.intsts1 & ATTCH)
			usbhs_mod_call(priv, irq_attch, priv, &irq_state);

		if (irq_state.intsts1 & DTCH)
			usbhs_mod_call(priv, irq_dtch, priv, &irq_state);

		if (irq_state.intsts1 & SIGN)
			usbhs_mod_call(priv, irq_sign, priv, &irq_state);

		if (irq_state.intsts1 & SACK)
			usbhs_mod_call(priv, irq_sack, priv, &irq_state);
	}
	return IRQ_HANDLED;
}