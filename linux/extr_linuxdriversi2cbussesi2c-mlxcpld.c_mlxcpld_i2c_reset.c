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
typedef  int /*<<< orphan*/  u8 ;
struct mlxcpld_i2c_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXCPLD_LPCI2C_CTRL_REG ; 
 int /*<<< orphan*/  MLXCPLD_LPCI2C_RST_SEL_MASK ; 
 int /*<<< orphan*/  mlxcpld_i2c_read_comm (struct mlxcpld_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlxcpld_i2c_write_comm (struct mlxcpld_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxcpld_i2c_reset(struct mlxcpld_i2c_priv *priv)
{
	u8 val;

	mutex_lock(&priv->lock);

	mlxcpld_i2c_read_comm(priv, MLXCPLD_LPCI2C_CTRL_REG, &val, 1);
	val &= ~MLXCPLD_LPCI2C_RST_SEL_MASK;
	mlxcpld_i2c_write_comm(priv, MLXCPLD_LPCI2C_CTRL_REG, &val, 1);

	mutex_unlock(&priv->lock);
}