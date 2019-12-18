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
struct vb2_queue {int dummy; } ;
struct rtl2832_sdr_platform_data {int /*<<< orphan*/  dvb_frontend; struct dvb_usb_device* dvb_usb_device; } ;
struct rtl2832_sdr_dev {int /*<<< orphan*/  v4l2_lock; scalar_t__ sequence; int /*<<< orphan*/  v4l2_subdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  udev; struct platform_device* pdev; } ;
struct TYPE_4__ {struct rtl2832_sdr_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct dvb_usb_device {TYPE_1__* props; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* frontend_ctrl ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* power_ctrl ) (struct dvb_usb_device*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  POWER_ON ; 
 scalar_t__ V4L2_SUBDEV_HAS_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtl2832_sdr_alloc_stream_bufs (struct rtl2832_sdr_dev*) ; 
 int rtl2832_sdr_alloc_urbs (struct rtl2832_sdr_dev*) ; 
 int rtl2832_sdr_set_adc (struct rtl2832_sdr_dev*) ; 
 int rtl2832_sdr_set_tuner (struct rtl2832_sdr_dev*) ; 
 int rtl2832_sdr_set_tuner_freq (struct rtl2832_sdr_dev*) ; 
 int rtl2832_sdr_submit_urbs (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dvb_usb_device*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rtl2832_sdr_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int rtl2832_sdr_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	struct platform_device *pdev = dev->pdev;
	struct rtl2832_sdr_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_usb_device *d = pdata->dvb_usb_device;
	int ret;

	dev_dbg(&pdev->dev, "\n");

	if (!dev->udev)
		return -ENODEV;

	if (mutex_lock_interruptible(&dev->v4l2_lock))
		return -ERESTARTSYS;

	if (d->props->power_ctrl)
		d->props->power_ctrl(d, 1);

	/* enable ADC */
	if (d->props->frontend_ctrl)
		d->props->frontend_ctrl(pdata->dvb_frontend, 1);

	set_bit(POWER_ON, &dev->flags);

	/* wake-up tuner */
	if (V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, core, s_power))
		ret = v4l2_subdev_call(dev->v4l2_subdev, core, s_power, 1);
	else
		ret = rtl2832_sdr_set_tuner(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_set_tuner_freq(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_set_adc(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_alloc_stream_bufs(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_alloc_urbs(dev);
	if (ret)
		goto err;

	dev->sequence = 0;

	ret = rtl2832_sdr_submit_urbs(dev);
	if (ret)
		goto err;

err:
	mutex_unlock(&dev->v4l2_lock);

	return ret;
}