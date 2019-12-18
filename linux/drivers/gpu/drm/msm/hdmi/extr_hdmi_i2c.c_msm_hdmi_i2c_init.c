#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int /*<<< orphan*/ * algo; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct hdmi_i2c_adapter {int /*<<< orphan*/  ddc_event; struct hdmi* hdmi; struct i2c_adapter base; } ;
struct hdmi {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct i2c_adapter* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct hdmi_i2c_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_hdmi_i2c_algorithm ; 
 int /*<<< orphan*/  msm_hdmi_i2c_destroy (struct i2c_adapter*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

struct i2c_adapter *msm_hdmi_i2c_init(struct hdmi *hdmi)
{
	struct hdmi_i2c_adapter *hdmi_i2c;
	struct i2c_adapter *i2c = NULL;
	int ret;

	hdmi_i2c = kzalloc(sizeof(*hdmi_i2c), GFP_KERNEL);
	if (!hdmi_i2c) {
		ret = -ENOMEM;
		goto fail;
	}

	i2c = &hdmi_i2c->base;

	hdmi_i2c->hdmi = hdmi;
	init_waitqueue_head(&hdmi_i2c->ddc_event);


	i2c->owner = THIS_MODULE;
	i2c->class = I2C_CLASS_DDC;
	snprintf(i2c->name, sizeof(i2c->name), "msm hdmi i2c");
	i2c->dev.parent = &hdmi->pdev->dev;
	i2c->algo = &msm_hdmi_i2c_algorithm;

	ret = i2c_add_adapter(i2c);
	if (ret)
		goto fail;

	return i2c;

fail:
	if (i2c)
		msm_hdmi_i2c_destroy(i2c);
	return ERR_PTR(ret);
}