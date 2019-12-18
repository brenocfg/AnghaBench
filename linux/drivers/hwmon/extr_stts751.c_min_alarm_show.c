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
struct stts751_priv {int notify_min; int min_alert; int /*<<< orphan*/  access_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct stts751_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stts751_update (struct stts751_priv*) ; 

__attribute__((used)) static ssize_t min_alarm_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	int ret;
	struct stts751_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->access_lock);
	ret = stts751_update(priv);
	if (!ret)
		priv->notify_min = true;
	mutex_unlock(&priv->access_lock);
	if (ret < 0)
		return ret;

	return snprintf(buf, PAGE_SIZE, "%d\n", priv->min_alert);
}