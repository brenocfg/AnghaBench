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
struct i2c_au1550_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_CTRL ; 
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  PSC_SMBCFG ; 
 int /*<<< orphan*/  WR (struct i2c_au1550_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_au1550_disable(struct i2c_au1550_data *priv)
{
	WR(priv, PSC_SMBCFG, 0);
	WR(priv, PSC_CTRL, PSC_CTRL_DISABLE);
}