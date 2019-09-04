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
struct mlxcpld_i2c_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct i2c_msg {scalar_t__ len; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mlxcpld_i2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mlxcpld_i2c_check_busy (struct mlxcpld_i2c_priv*) ; 
 int mlxcpld_i2c_check_msg_params (struct mlxcpld_i2c_priv*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  mlxcpld_i2c_reset (struct mlxcpld_i2c_priv*) ; 
 int /*<<< orphan*/  mlxcpld_i2c_set_transf_data (struct mlxcpld_i2c_priv*,struct i2c_msg*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxcpld_i2c_wait_for_free (struct mlxcpld_i2c_priv*) ; 
 int mlxcpld_i2c_wait_for_tc (struct mlxcpld_i2c_priv*) ; 
 int /*<<< orphan*/  mlxcpld_i2c_xfer_msg (struct mlxcpld_i2c_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxcpld_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			    int num)
{
	struct mlxcpld_i2c_priv *priv = i2c_get_adapdata(adap);
	u8 comm_len = 0;
	int i, err;

	err = mlxcpld_i2c_check_msg_params(priv, msgs, num);
	if (err) {
		dev_err(priv->dev, "Incorrect message\n");
		return err;
	}

	for (i = 0; i < num; ++i)
		comm_len += msgs[i].len;

	/* Check bus state */
	if (mlxcpld_i2c_wait_for_free(priv)) {
		dev_err(priv->dev, "LPCI2C bridge is busy\n");

		/*
		 * Usually it means something serious has happened.
		 * We can not have unfinished previous transfer
		 * so it doesn't make any sense to try to stop it.
		 * Probably we were not able to recover from the
		 * previous error.
		 * The only reasonable thing - is soft reset.
		 */
		mlxcpld_i2c_reset(priv);
		if (mlxcpld_i2c_check_busy(priv)) {
			dev_err(priv->dev, "LPCI2C bridge is busy after reset\n");
			return -EIO;
		}
	}

	mlxcpld_i2c_set_transf_data(priv, msgs, num, comm_len);

	mutex_lock(&priv->lock);

	/* Do real transfer. Can't fail */
	mlxcpld_i2c_xfer_msg(priv);

	/* Wait for transaction complete */
	err = mlxcpld_i2c_wait_for_tc(priv);

	mutex_unlock(&priv->lock);

	return err < 0 ? err : num;
}