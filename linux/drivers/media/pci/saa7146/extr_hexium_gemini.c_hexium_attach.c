#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct saa7146_pci_extension_data {int dummy; } ;
struct saa7146_dev {struct hexium* ext_priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct hexium {TYPE_4__ i2c_adapter; int /*<<< orphan*/  video_dev; scalar_t__ cur_input; int /*<<< orphan*/  cur_std; } ;
struct TYPE_7__ {int /*<<< orphan*/  vidioc_s_input; int /*<<< orphan*/  vidioc_g_input; int /*<<< orphan*/  vidioc_enum_input; } ;
struct TYPE_8__ {TYPE_1__ vid_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD1_INIT ; 
 int /*<<< orphan*/  DD1_STREAM_B ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int /*<<< orphan*/  DEB_S (char*) ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MASK_08 ; 
 int MASK_09 ; 
 int MASK_10 ; 
 int MASK_24 ; 
 int MASK_25 ; 
 int MASK_26 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  SAA7146_I2C_BUS_BIT_RATE_480 ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  hexium_init_done (struct saa7146_dev*) ; 
 int /*<<< orphan*/  hexium_num ; 
 int /*<<< orphan*/  hexium_pal ; 
 int /*<<< orphan*/  hexium_set_input (struct hexium*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexium_set_standard (struct hexium*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_add_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct hexium*) ; 
 struct hexium* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_i2c_adapter_prepare (struct saa7146_dev*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int saa7146_register_device (int /*<<< orphan*/ *,struct saa7146_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_vv_init (struct saa7146_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  saa7146_vv_release (struct saa7146_dev*) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vidioc_enum_input ; 
 int /*<<< orphan*/  vidioc_g_input ; 
 int /*<<< orphan*/  vidioc_s_input ; 
 TYPE_2__ vv_data ; 

__attribute__((used)) static int hexium_attach(struct saa7146_dev *dev, struct saa7146_pci_extension_data *info)
{
	struct hexium *hexium;
	int ret;

	DEB_EE("\n");

	hexium = kzalloc(sizeof(*hexium), GFP_KERNEL);
	if (!hexium)
		return -ENOMEM;

	dev->ext_priv = hexium;

	/* enable i2c-port pins */
	saa7146_write(dev, MC1, (MASK_08 | MASK_24 | MASK_10 | MASK_26));

	strscpy(hexium->i2c_adapter.name, "hexium gemini",
		sizeof(hexium->i2c_adapter.name));
	saa7146_i2c_adapter_prepare(dev, &hexium->i2c_adapter, SAA7146_I2C_BUS_BIT_RATE_480);
	if (i2c_add_adapter(&hexium->i2c_adapter) < 0) {
		DEB_S("cannot register i2c-device. skipping.\n");
		kfree(hexium);
		return -EFAULT;
	}

	/*  set HWControl GPIO number 2 */
	saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	saa7146_write(dev, DD1_INIT, 0x07000700);
	saa7146_write(dev, DD1_STREAM_B, 0x00000000);
	saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	/* the rest */
	hexium->cur_input = 0;
	hexium_init_done(dev);

	hexium_set_standard(hexium, hexium_pal);
	hexium->cur_std = V4L2_STD_PAL;

	hexium_set_input(hexium, 0);
	hexium->cur_input = 0;

	saa7146_vv_init(dev, &vv_data);

	vv_data.vid_ops.vidioc_enum_input = vidioc_enum_input;
	vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data.vid_ops.vidioc_s_input = vidioc_s_input;
	ret = saa7146_register_device(&hexium->video_dev, dev, "hexium gemini", VFL_TYPE_GRABBER);
	if (ret < 0) {
		pr_err("cannot register capture v4l2 device. skipping.\n");
		saa7146_vv_release(dev);
		i2c_del_adapter(&hexium->i2c_adapter);
		kfree(hexium);
		return ret;
	}

	pr_info("found 'hexium gemini' frame grabber-%d\n", hexium_num);
	hexium_num++;

	return 0;
}