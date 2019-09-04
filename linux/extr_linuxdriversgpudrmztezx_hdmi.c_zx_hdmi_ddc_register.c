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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct zx_hdmi_i2c {struct i2c_adapter adap; int /*<<< orphan*/  lock; } ;
struct zx_hdmi {int /*<<< orphan*/  dev; struct zx_hdmi_i2c* ddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct zx_hdmi_i2c* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct zx_hdmi*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  zx_hdmi_algorithm ; 

__attribute__((used)) static int zx_hdmi_ddc_register(struct zx_hdmi *hdmi)
{
	struct i2c_adapter *adap;
	struct zx_hdmi_i2c *ddc;
	int ret;

	ddc = devm_kzalloc(hdmi->dev, sizeof(*ddc), GFP_KERNEL);
	if (!ddc)
		return -ENOMEM;

	hdmi->ddc = ddc;
	mutex_init(&ddc->lock);

	adap = &ddc->adap;
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DDC;
	adap->dev.parent = hdmi->dev;
	adap->algo = &zx_hdmi_algorithm;
	snprintf(adap->name, sizeof(adap->name), "zx hdmi i2c");

	ret = i2c_add_adapter(adap);
	if (ret) {
		DRM_DEV_ERROR(hdmi->dev, "failed to add I2C adapter: %d\n",
			      ret);
		return ret;
	}

	i2c_set_adapdata(adap, hdmi);

	return 0;
}