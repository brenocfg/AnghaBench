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
struct emac_priv {scalar_t__ version; int /*<<< orphan*/  (* int_enable ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_CTRL_EWCTL ; 
 int /*<<< orphan*/  EMAC_DM646X_CMRXINTEN ; 
 int /*<<< orphan*/  EMAC_DM646X_CMTXINTEN ; 
 scalar_t__ EMAC_VERSION_2 ; 
 int /*<<< orphan*/  emac_ctrl_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void emac_int_enable(struct emac_priv *priv)
{
	if (priv->version == EMAC_VERSION_2) {
		if (priv->int_enable)
			priv->int_enable();

		emac_ctrl_write(EMAC_DM646X_CMRXINTEN, 0xff);
		emac_ctrl_write(EMAC_DM646X_CMTXINTEN, 0xff);

		/* In addition to turning on interrupt Enable, we need
		 * ack by writing appropriate values to the EOI
		 * register */

		/* NOTE: Rx Threshold and Misc interrupts are not enabled */
	} else {
		/* Set DM644x control registers for interrupt control */
		emac_ctrl_write(EMAC_CTRL_EWCTL, 0x1);
	}
}