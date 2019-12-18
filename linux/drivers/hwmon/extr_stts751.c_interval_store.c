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
struct stts751_priv {int interval; int /*<<< orphan*/  access_lock; TYPE_1__* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  STTS751_REG_RATE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct stts751_priv* dev_get_drvdata (struct device*) ; 
 int find_closest_descending (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stts751_adjust_resolution (struct stts751_priv*) ; 
 int /*<<< orphan*/ * stts751_intervals ; 

__attribute__((used)) static ssize_t interval_store(struct device *dev,
			      struct device_attribute *attr, const char *buf,
			      size_t count)
{
	unsigned long val;
	int idx;
	int ret = count;
	struct stts751_priv *priv = dev_get_drvdata(dev);

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;

	idx = find_closest_descending(val, stts751_intervals,
				      ARRAY_SIZE(stts751_intervals));

	dev_dbg(&priv->client->dev, "setting interval. req:%lu, idx: %d, val: %d",
		val, idx, stts751_intervals[idx]);

	mutex_lock(&priv->access_lock);
	if (priv->interval == idx)
		goto exit;

	/*
	 * In early development stages I've become suspicious about the chip
	 * starting to misbehave if I ever set, even briefly, an invalid
	 * configuration. While I'm not sure this is really needed, be
	 * conservative and set rate/resolution in such an order that avoids
	 * passing through an invalid configuration.
	 */

	/* speed up: lower the resolution, then modify convrate */
	if (priv->interval < idx) {
		dev_dbg(&priv->client->dev, "lower resolution, then modify convrate");
		priv->interval = idx;
		ret = stts751_adjust_resolution(priv);
		if (ret)
			goto exit;
	}

	ret = i2c_smbus_write_byte_data(priv->client, STTS751_REG_RATE, idx);
	if (ret)
		goto exit;
	/* slow down: modify convrate, then raise resolution */
	if (priv->interval != idx) {
		dev_dbg(&priv->client->dev, "modify convrate, then raise resolution");
		priv->interval = idx;
		ret = stts751_adjust_resolution(priv);
		if (ret)
			goto exit;
	}
	ret = count;
exit:
	mutex_unlock(&priv->access_lock);

	return ret;
}