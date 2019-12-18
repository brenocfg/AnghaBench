#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xlr_i2c_private {TYPE_1__* cfg; } ;
struct TYPE_2__ {int status_busy; } ;

/* Variables and functions */
 int XLR_I2C_BUS_BUSY ; 

__attribute__((used)) static int xlr_i2c_busy(struct xlr_i2c_private *priv, u32 status)
{
	return (status & XLR_I2C_BUS_BUSY) == priv->cfg->status_busy;
}