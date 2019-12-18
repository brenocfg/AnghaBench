#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int error; } ;
struct saa7146_dev {struct mxb* ext_priv; int /*<<< orphan*/  v4l2_dev; struct v4l2_ctrl_handler ctrl_handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct mxb {TYPE_1__ i2c_adapter; void* tuner; void* saa7111a; void* tda9840; void* tea6415c; void* tea6420_2; void* tea6420_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_S (char*) ; 
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_SAA7111A ; 
 int /*<<< orphan*/  I2C_TDA9840 ; 
 int /*<<< orphan*/  I2C_TEA6415C ; 
 int /*<<< orphan*/  I2C_TEA6420_1 ; 
 int /*<<< orphan*/  I2C_TEA6420_2 ; 
 int /*<<< orphan*/  I2C_TUNER ; 
 int /*<<< orphan*/  SAA7146_I2C_BUS_BIT_RATE_480 ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 scalar_t__ i2c_add_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct mxb*) ; 
 struct mxb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxb_ctrl_ops ; 
 int mxb_num ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  saa7146_i2c_adapter_prepare (struct saa7146_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 void* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxb_probe(struct saa7146_dev *dev)
{
	struct v4l2_ctrl_handler *hdl = &dev->ctrl_handler;
	struct mxb *mxb = NULL;

	v4l2_ctrl_new_std(hdl, &mxb_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	if (hdl->error)
		return hdl->error;
	mxb = kzalloc(sizeof(struct mxb), GFP_KERNEL);
	if (mxb == NULL) {
		DEB_D("not enough kernel memory\n");
		return -ENOMEM;
	}


	snprintf(mxb->i2c_adapter.name, sizeof(mxb->i2c_adapter.name), "mxb%d", mxb_num);

	saa7146_i2c_adapter_prepare(dev, &mxb->i2c_adapter, SAA7146_I2C_BUS_BIT_RATE_480);
	if (i2c_add_adapter(&mxb->i2c_adapter) < 0) {
		DEB_S("cannot register i2c-device. skipping.\n");
		kfree(mxb);
		return -EFAULT;
	}

	mxb->saa7111a = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"saa7111", I2C_SAA7111A, NULL);
	mxb->tea6420_1 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tea6420", I2C_TEA6420_1, NULL);
	mxb->tea6420_2 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tea6420", I2C_TEA6420_2, NULL);
	mxb->tea6415c = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tea6415c", I2C_TEA6415C, NULL);
	mxb->tda9840 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tda9840", I2C_TDA9840, NULL);
	mxb->tuner = v4l2_i2c_new_subdev(&dev->v4l2_dev, &mxb->i2c_adapter,
			"tuner", I2C_TUNER, NULL);

	/* check if all devices are present */
	if (!mxb->tea6420_1 || !mxb->tea6420_2 || !mxb->tea6415c ||
	    !mxb->tda9840 || !mxb->saa7111a || !mxb->tuner) {
		pr_err("did not find all i2c devices. aborting\n");
		i2c_del_adapter(&mxb->i2c_adapter);
		kfree(mxb);
		return -ENODEV;
	}

	/* all devices are present, probe was successful */

	/* we store the pointer in our private data field */
	dev->ext_priv = mxb;

	v4l2_ctrl_handler_setup(hdl);

	return 0;
}