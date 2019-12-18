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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cxd2841er_priv {TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*) ; 

__attribute__((used)) static void cxd2841er_i2c_debug(struct cxd2841er_priv *priv,
				u8 addr, u8 reg, u8 write,
				const u8 *data, u32 len)
{
	dev_dbg(&priv->i2c->dev,
		"cxd2841er: I2C %s addr %02x reg 0x%02x size %d data %*ph\n",
		(write == 0 ? "read" : "write"), addr, reg, len, len, data);
}