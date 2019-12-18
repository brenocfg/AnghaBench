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
struct ov2680_dev {int /*<<< orphan*/  lock; struct i2c_client* i2c_client; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct ov2680_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov2680_check_id (struct ov2680_dev*) ; 
 int ov2680_get_regulators (struct ov2680_dev*) ; 
 int ov2680_mode_init (struct ov2680_dev*) ; 
 int ov2680_parse_dt (struct ov2680_dev*) ; 
 int ov2680_v4l2_register (struct ov2680_dev*) ; 

__attribute__((used)) static int ov2680_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct ov2680_dev *sensor;
	int ret;

	sensor = devm_kzalloc(dev, sizeof(*sensor), GFP_KERNEL);
	if (!sensor)
		return -ENOMEM;

	sensor->i2c_client = client;

	ret = ov2680_parse_dt(sensor);
	if (ret < 0)
		return -EINVAL;

	ret = ov2680_mode_init(sensor);
	if (ret < 0)
		return ret;

	ret = ov2680_get_regulators(sensor);
	if (ret < 0) {
		dev_err(dev, "failed to get regulators\n");
		return ret;
	}

	mutex_init(&sensor->lock);

	ret = ov2680_check_id(sensor);
	if (ret < 0)
		goto lock_destroy;

	ret = ov2680_v4l2_register(sensor);
	if (ret < 0)
		goto lock_destroy;

	dev_info(dev, "ov2680 init correctly\n");

	return 0;

lock_destroy:
	dev_err(dev, "ov2680 init fail: %d\n", ret);
	mutex_destroy(&sensor->lock);

	return ret;
}