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
typedef  int u16 ;
struct usbhs_priv {int dummy; } ;
struct usbhs_mod_info {scalar_t__ irq_vbus; } ;
struct usbhs_mod {int irq_bempsts; int irq_brdysts; scalar_t__ irq_sack; scalar_t__ irq_sign; scalar_t__ irq_dtch; scalar_t__ irq_attch; scalar_t__ irq_ready; scalar_t__ irq_empty; scalar_t__ irq_ctrl_stage; } ;

/* Variables and functions */
 int ATTCHE ; 
 int BEMPE ; 
 int /*<<< orphan*/  BEMPENB ; 
 int BRDYE ; 
 int /*<<< orphan*/  BRDYENB ; 
 int CTRE ; 
 int DTCHE ; 
 int /*<<< orphan*/  INTENB0 ; 
 int /*<<< orphan*/  INTENB1 ; 
 int SACKE ; 
 int SIGNE ; 
 int VBSE ; 
 scalar_t__ usbhs_mod_is_host (struct usbhs_priv*) ; 
 struct usbhs_mod_info* usbhs_priv_to_modinfo (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int) ; 

void usbhs_irq_callback_update(struct usbhs_priv *priv, struct usbhs_mod *mod)
{
	u16 intenb0 = 0;
	u16 intenb1 = 0;
	struct usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	/*
	 * BEMPENB/BRDYENB are picky.
	 * below method is required
	 *
	 *  - clear  INTSTS0
	 *  - update BEMPENB/BRDYENB
	 *  - update INTSTS0
	 */
	usbhs_write(priv, INTENB0, 0);
	if (usbhs_mod_is_host(priv))
		usbhs_write(priv, INTENB1, 0);

	usbhs_write(priv, BEMPENB, 0);
	usbhs_write(priv, BRDYENB, 0);

	/*
	 * see also
	 *	usbhs_interrupt
	 */

	/*
	 * it don't enable DVSE (intenb0) here
	 * but "mod->irq_dev_state" will be called.
	 */
	if (info->irq_vbus)
		intenb0 |= VBSE;

	if (mod) {
		/*
		 * INTSTS0
		 */
		if (mod->irq_ctrl_stage)
			intenb0 |= CTRE;

		if (mod->irq_empty && mod->irq_bempsts) {
			usbhs_write(priv, BEMPENB, mod->irq_bempsts);
			intenb0 |= BEMPE;
		}

		if (mod->irq_ready && mod->irq_brdysts) {
			usbhs_write(priv, BRDYENB, mod->irq_brdysts);
			intenb0 |= BRDYE;
		}

		if (usbhs_mod_is_host(priv)) {
			/*
			 * INTSTS1
			 */
			if (mod->irq_attch)
				intenb1 |= ATTCHE;

			if (mod->irq_dtch)
				intenb1 |= DTCHE;

			if (mod->irq_sign)
				intenb1 |= SIGNE;

			if (mod->irq_sack)
				intenb1 |= SACKE;
		}
	}

	if (intenb0)
		usbhs_write(priv, INTENB0, intenb0);

	if (usbhs_mod_is_host(priv) && intenb1)
		usbhs_write(priv, INTENB1, intenb1);
}