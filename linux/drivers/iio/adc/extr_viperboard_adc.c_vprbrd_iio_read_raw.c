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
struct vprbrd_adc_msg {int val; int /*<<< orphan*/  chan; int /*<<< orphan*/  cmd; } ;
struct vprbrd_adc {struct vprbrd* vb; } ;
struct vprbrd {int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_dev; scalar_t__ buf; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  VPRBRD_ADC_CMD_GET ; 
 int /*<<< orphan*/  VPRBRD_USB_REQUEST_ADC ; 
 int /*<<< orphan*/  VPRBRD_USB_TIMEOUT_MS ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_IN ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct vprbrd_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct vprbrd_adc_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vprbrd_iio_read_raw(struct iio_dev *iio_dev,
				struct iio_chan_spec const *chan,
				int *val,
				int *val2,
				long info)
{
	int ret, error = 0;
	struct vprbrd_adc *adc = iio_priv(iio_dev);
	struct vprbrd *vb = adc->vb;
	struct vprbrd_adc_msg *admsg = (struct vprbrd_adc_msg *)vb->buf;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&vb->lock);

		admsg->cmd = VPRBRD_ADC_CMD_GET;
		admsg->chan = chan->channel;
		admsg->val = 0x00;

		ret = usb_control_msg(vb->usb_dev,
			usb_sndctrlpipe(vb->usb_dev, 0), VPRBRD_USB_REQUEST_ADC,
			VPRBRD_USB_TYPE_OUT, 0x0000, 0x0000, admsg,
			sizeof(struct vprbrd_adc_msg), VPRBRD_USB_TIMEOUT_MS);
		if (ret != sizeof(struct vprbrd_adc_msg)) {
			dev_err(&iio_dev->dev, "usb send error on adc read\n");
			error = -EREMOTEIO;
		}

		ret = usb_control_msg(vb->usb_dev,
			usb_rcvctrlpipe(vb->usb_dev, 0), VPRBRD_USB_REQUEST_ADC,
			VPRBRD_USB_TYPE_IN, 0x0000, 0x0000, admsg,
			sizeof(struct vprbrd_adc_msg), VPRBRD_USB_TIMEOUT_MS);

		*val = admsg->val;

		mutex_unlock(&vb->lock);

		if (ret != sizeof(struct vprbrd_adc_msg)) {
			dev_err(&iio_dev->dev, "usb recv error on adc read\n");
			error = -EREMOTEIO;
		}

		if (error)
			goto error;

		return IIO_VAL_INT;
	default:
		error = -EINVAL;
		break;
	}
error:
	return error;
}