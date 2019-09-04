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
struct i2c_demux_pinctrl_priv {unsigned int num_chan; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct i2c_demux_pinctrl_priv* dev_get_drvdata (struct device*) ; 
 int i2c_demux_change_master (struct i2c_demux_pinctrl_priv*,unsigned int) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static ssize_t current_master_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct i2c_demux_pinctrl_priv *priv = dev_get_drvdata(dev);
	unsigned int val;
	int ret;

	ret = kstrtouint(buf, 0, &val);
	if (ret < 0)
		return ret;

	if (val >= priv->num_chan)
		return -EINVAL;

	ret = i2c_demux_change_master(priv, val);

	return ret < 0 ? ret : count;
}