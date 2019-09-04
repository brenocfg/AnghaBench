#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  class; } ;
struct inno_hdmi_i2c {struct i2c_adapter adap; int /*<<< orphan*/  cmp; int /*<<< orphan*/  lock; } ;
struct inno_hdmi {TYPE_2__* dev; struct inno_hdmi_i2c* i2c; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_INFO (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct i2c_adapter* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (TYPE_2__*,struct inno_hdmi_i2c*) ; 
 struct inno_hdmi_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct inno_hdmi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inno_hdmi_algorithm ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct i2c_adapter *inno_hdmi_i2c_adapter(struct inno_hdmi *hdmi)
{
	struct i2c_adapter *adap;
	struct inno_hdmi_i2c *i2c;
	int ret;

	i2c = devm_kzalloc(hdmi->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return ERR_PTR(-ENOMEM);

	mutex_init(&i2c->lock);
	init_completion(&i2c->cmp);

	adap = &i2c->adap;
	adap->class = I2C_CLASS_DDC;
	adap->owner = THIS_MODULE;
	adap->dev.parent = hdmi->dev;
	adap->dev.of_node = hdmi->dev->of_node;
	adap->algo = &inno_hdmi_algorithm;
	strlcpy(adap->name, "Inno HDMI", sizeof(adap->name));
	i2c_set_adapdata(adap, hdmi);

	ret = i2c_add_adapter(adap);
	if (ret) {
		dev_warn(hdmi->dev, "cannot add %s I2C adapter\n", adap->name);
		devm_kfree(hdmi->dev, i2c);
		return ERR_PTR(ret);
	}

	hdmi->i2c = i2c;

	DRM_DEV_INFO(hdmi->dev, "registered %s I2C bus driver\n", adap->name);

	return adap;
}