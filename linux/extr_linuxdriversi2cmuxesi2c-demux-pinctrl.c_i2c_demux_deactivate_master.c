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
struct i2c_demux_pinctrl_priv {int cur_chan; TYPE_1__* chan; int /*<<< orphan*/  cur_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent_adap; int /*<<< orphan*/  chgset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ *) ; 
 int of_changeset_revert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_demux_deactivate_master(struct i2c_demux_pinctrl_priv *priv)
{
	int ret, cur = priv->cur_chan;

	if (cur < 0)
		return 0;

	i2c_del_adapter(&priv->cur_adap);
	i2c_put_adapter(priv->chan[cur].parent_adap);

	ret = of_changeset_revert(&priv->chan[cur].chgset);

	priv->chan[cur].parent_adap = NULL;
	priv->cur_chan = -EINVAL;

	return ret;
}