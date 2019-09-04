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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct hix5hd2_i2c_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int hix5hd2_i2c_xfer_msg (struct hix5hd2_i2c_priv*,struct i2c_msg*,int) ; 
 struct hix5hd2_i2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hix5hd2_i2c_xfer(struct i2c_adapter *adap,
			    struct i2c_msg *msgs, int num)
{
	struct hix5hd2_i2c_priv *priv = i2c_get_adapdata(adap);
	int i, ret, stop;

	pm_runtime_get_sync(priv->dev);

	for (i = 0; i < num; i++, msgs++) {
		stop = (i == num - 1);
		ret = hix5hd2_i2c_xfer_msg(priv, msgs, stop);
		if (ret < 0)
			goto out;
	}

	ret = num;

out:
	pm_runtime_mark_last_busy(priv->dev);
	pm_runtime_put_autosuspend(priv->dev);
	return ret;
}