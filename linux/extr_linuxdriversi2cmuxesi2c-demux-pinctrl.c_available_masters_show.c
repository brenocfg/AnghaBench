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
struct i2c_demux_pinctrl_priv {int num_chan; TYPE_1__* chan; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent_np; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct i2c_demux_pinctrl_priv* dev_get_drvdata (struct device*) ; 
 scalar_t__ scnprintf (char*,int,char*,int,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static ssize_t available_masters_show(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct i2c_demux_pinctrl_priv *priv = dev_get_drvdata(dev);
	int count = 0, i;

	for (i = 0; i < priv->num_chan && count < PAGE_SIZE; i++)
		count += scnprintf(buf + count, PAGE_SIZE - count, "%d:%pOF%c",
				   i, priv->chan[i].parent_np,
				   i == priv->num_chan - 1 ? '\n' : ' ');

	return count;
}