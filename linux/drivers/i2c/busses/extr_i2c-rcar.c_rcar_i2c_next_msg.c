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
struct rcar_i2c_priv {int /*<<< orphan*/  flags; int /*<<< orphan*/  msgs_left; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID_P_MASK ; 
 int /*<<< orphan*/  rcar_i2c_prepare_msg (struct rcar_i2c_priv*) ; 

__attribute__((used)) static void rcar_i2c_next_msg(struct rcar_i2c_priv *priv)
{
	priv->msg++;
	priv->msgs_left--;
	priv->flags &= ID_P_MASK;
	rcar_i2c_prepare_msg(priv);
}