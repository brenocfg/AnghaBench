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
struct rcar_i2c_priv {int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int LOOP_TIMEOUT ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 
 int reset_control_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rcar_i2c_do_reset(struct rcar_i2c_priv *priv)
{
	int i, ret;

	ret = reset_control_reset(priv->rstc);
	if (ret)
		return ret;

	for (i = 0; i < LOOP_TIMEOUT; i++) {
		ret = reset_control_status(priv->rstc);
		if (ret == 0)
			return 0;
		udelay(1);
	}

	return -ETIMEDOUT;
}