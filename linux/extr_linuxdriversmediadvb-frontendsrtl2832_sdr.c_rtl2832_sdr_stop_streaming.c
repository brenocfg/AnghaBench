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
struct rtl2832_sdr_dev {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  v4l2_subdev; struct platform_device* pdev; } ;
struct TYPE_4__ {struct rtl2832_sdr_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct dvb_usb_device {TYPE_1__* props; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* power_ctrl ) (struct dvb_usb_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* frontend_ctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_ON ; 
 scalar_t__ V4L2_SUBDEV_HAS_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl2832_sdr_cleanup_queued_bufs (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  rtl2832_sdr_free_stream_bufs (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  rtl2832_sdr_free_urbs (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  rtl2832_sdr_kill_urbs (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  rtl2832_sdr_unset_adc (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  rtl2832_sdr_unset_tuner (struct rtl2832_sdr_dev*) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dvb_usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl2832_sdr_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void rtl2832_sdr_stop_streaming(struct vb2_queue *vq)
{
	struct rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	struct platform_device *pdev = dev->pdev;
	struct rtl2832_sdr_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_usb_device *d = pdata->dvb_usb_device;

	dev_dbg(&pdev->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	rtl2832_sdr_kill_urbs(dev);
	rtl2832_sdr_free_urbs(dev);
	rtl2832_sdr_free_stream_bufs(dev);
	rtl2832_sdr_cleanup_queued_bufs(dev);
	rtl2832_sdr_unset_adc(dev);

	/* sleep tuner */
	if (V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, core, s_power))
		v4l2_subdev_call(dev->v4l2_subdev, core, s_power, 0);
	else
		rtl2832_sdr_unset_tuner(dev);

	clear_bit(POWER_ON, &dev->flags);

	/* disable ADC */
	if (d->props->frontend_ctrl)
		d->props->frontend_ctrl(pdata->dvb_frontend, 0);

	if (d->props->power_ctrl)
		d->props->power_ctrl(d, 0);

	mutex_unlock(&dev->v4l2_lock);
}