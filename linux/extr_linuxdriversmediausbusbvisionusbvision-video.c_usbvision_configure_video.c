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
struct usb_usbvision {int dev_model; double radio_freq; int tv_freq; scalar_t__ ctl_input; int /*<<< orphan*/  video_inputs; int /*<<< orphan*/  tvnorm_id; scalar_t__ vin_reg2_preset; int /*<<< orphan*/  palette; } ;
struct TYPE_2__ {scalar_t__ audio_channels; int /*<<< orphan*/  video_channels; int /*<<< orphan*/  video_norm; scalar_t__ vin_reg2; scalar_t__ vin_reg2_override; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbvision_audio_off (struct usb_usbvision*) ; 
 TYPE_1__* usbvision_device_data ; 
 int /*<<< orphan*/  usbvision_i2c_register (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_power_on (struct usb_usbvision*) ; 
 int /*<<< orphan*/ * usbvision_v4l2_format ; 

__attribute__((used)) static void usbvision_configure_video(struct usb_usbvision *usbvision)
{
	int model;

	if (!usbvision)
		return;

	model = usbvision->dev_model;
	usbvision->palette = usbvision_v4l2_format[2]; /* V4L2_PIX_FMT_RGB24; */

	if (usbvision_device_data[usbvision->dev_model].vin_reg2_override) {
		usbvision->vin_reg2_preset =
			usbvision_device_data[usbvision->dev_model].vin_reg2;
	} else {
		usbvision->vin_reg2_preset = 0;
	}

	usbvision->tvnorm_id = usbvision_device_data[model].video_norm;
	usbvision->video_inputs = usbvision_device_data[model].video_channels;
	usbvision->ctl_input = 0;
	usbvision->radio_freq = 87.5 * 16000;
	usbvision->tv_freq = 400 * 16;

	/* This should be here to make i2c clients to be able to register */
	/* first switch off audio */
	if (usbvision_device_data[model].audio_channels > 0)
		usbvision_audio_off(usbvision);
	/* and then power up the tuner */
	usbvision_power_on(usbvision);
	usbvision_i2c_register(usbvision);
}