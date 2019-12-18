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
struct xlr_i2c_private {int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLR_I2C_STATUS ; 
 int /*<<< orphan*/  xlr_i2c_busy (struct xlr_i2c_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_i2c_rdreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlr_i2c_idle(struct xlr_i2c_private *priv)
{
	return !xlr_i2c_busy(priv, xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS));
}