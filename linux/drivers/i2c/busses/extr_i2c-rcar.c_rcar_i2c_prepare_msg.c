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
struct rcar_i2c_priv {int msgs_left; int flags; int /*<<< orphan*/  msg; scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMAR ; 
 int /*<<< orphan*/  ICMCR ; 
 int /*<<< orphan*/  ICMIER ; 
 int /*<<< orphan*/  ICMSR ; 
 int ID_FIRST_MSG ; 
 int ID_LAST_MSG ; 
 int ID_P_REP_AFTER_RD ; 
 int /*<<< orphan*/  RCAR_BUS_PHASE_START ; 
 int /*<<< orphan*/  RCAR_IRQ_RECV ; 
 int /*<<< orphan*/  RCAR_IRQ_SEND ; 
 int /*<<< orphan*/  i2c_8bit_addr_from_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_i2c_is_recv (struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  rcar_i2c_write (struct rcar_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_i2c_prepare_msg(struct rcar_i2c_priv *priv)
{
	int read = !!rcar_i2c_is_recv(priv);

	priv->pos = 0;
	if (priv->msgs_left == 1)
		priv->flags |= ID_LAST_MSG;

	rcar_i2c_write(priv, ICMAR, i2c_8bit_addr_from_msg(priv->msg));
	/*
	 * We don't have a test case but the HW engineers say that the write order
	 * of ICMSR and ICMCR depends on whether we issue START or REP_START. Since
	 * it didn't cause a drawback for me, let's rather be safe than sorry.
	 */
	if (priv->flags & ID_FIRST_MSG) {
		rcar_i2c_write(priv, ICMSR, 0);
		rcar_i2c_write(priv, ICMCR, RCAR_BUS_PHASE_START);
	} else {
		if (priv->flags & ID_P_REP_AFTER_RD)
			priv->flags &= ~ID_P_REP_AFTER_RD;
		else
			rcar_i2c_write(priv, ICMCR, RCAR_BUS_PHASE_START);
		rcar_i2c_write(priv, ICMSR, 0);
	}
	rcar_i2c_write(priv, ICMIER, read ? RCAR_IRQ_RECV : RCAR_IRQ_SEND);
}