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
struct arc_emac_priv {int dummy; } ;

/* Variables and functions */
 int ARC_MDIO_COMPLETE_POLL_COUNT ; 
 int ETIMEDOUT ; 
 unsigned int MDIO_MASK ; 
 int /*<<< orphan*/  R_STATUS ; 
 unsigned int arc_reg_get (struct arc_emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_reg_set (struct arc_emac_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int arc_mdio_complete_wait(struct arc_emac_priv *priv)
{
	unsigned int i;

	for (i = 0; i < ARC_MDIO_COMPLETE_POLL_COUNT * 40; i++) {
		unsigned int status = arc_reg_get(priv, R_STATUS);

		status &= MDIO_MASK;

		if (status) {
			/* Reset "MDIO complete" flag */
			arc_reg_set(priv, R_STATUS, status);
			return 0;
		}

		msleep(25);
	}

	return -ETIMEDOUT;
}