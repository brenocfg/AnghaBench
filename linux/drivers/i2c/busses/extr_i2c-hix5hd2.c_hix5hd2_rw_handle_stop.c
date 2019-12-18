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
struct hix5hd2_i2c_priv {scalar_t__ regs; int /*<<< orphan*/  state; scalar_t__ stop; } ;

/* Variables and functions */
 scalar_t__ HIX5I2C_COM ; 
 int /*<<< orphan*/  HIX5I2C_STAT_SND_STOP ; 
 int /*<<< orphan*/  I2C_STOP ; 
 int /*<<< orphan*/  hix5hd2_rw_over (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hix5hd2_rw_handle_stop(struct hix5hd2_i2c_priv *priv)
{
	if (priv->stop) {
		priv->state = HIX5I2C_STAT_SND_STOP;
		writel_relaxed(I2C_STOP, priv->regs + HIX5I2C_COM);
	} else {
		hix5hd2_rw_over(priv);
	}
}