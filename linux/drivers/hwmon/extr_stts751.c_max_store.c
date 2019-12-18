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
struct stts751_priv {long event_max; int /*<<< orphan*/  access_lock; TYPE_1__* client; int /*<<< orphan*/  event_min; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STTS751_REG_HLIM_H ; 
 int /*<<< orphan*/  STTS751_REG_HLIM_L ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,long) ; 
 struct stts751_priv* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stts751_set_temp_reg16 (struct stts751_priv*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t max_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	int ret;
	long temp;
	struct stts751_priv *priv = dev_get_drvdata(dev);

	if (kstrtol(buf, 10, &temp) < 0)
		return -EINVAL;

	mutex_lock(&priv->access_lock);
	/* HW works in range -64C to +127.937C */
	temp = clamp_val(temp, priv->event_min, 127937);
	ret = stts751_set_temp_reg16(priv, temp,
				     STTS751_REG_HLIM_H, STTS751_REG_HLIM_L);
	if (ret)
		goto exit;

	dev_dbg(&priv->client->dev, "setting event max %ld", temp);
	priv->event_max = temp;
	ret = count;
exit:
	mutex_unlock(&priv->access_lock);
	return ret;
}