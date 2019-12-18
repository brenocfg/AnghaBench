#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct ff_effect* old; struct ff_effect* effect; } ;
struct TYPE_7__ {TYPE_4__ upload; } ;
struct uinput_request {TYPE_3__ u; int /*<<< orphan*/  code; } ;
struct uinput_device {int dummy; } ;
struct input_dev {int dummy; } ;
struct TYPE_5__ {scalar_t__ waveform; } ;
struct TYPE_6__ {TYPE_1__ periodic; } ;
struct ff_effect {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FF_CUSTOM ; 
 scalar_t__ FF_PERIODIC ; 
 int /*<<< orphan*/  UI_FF_UPLOAD ; 
 struct uinput_device* input_get_drvdata (struct input_dev*) ; 
 int uinput_request_submit (struct uinput_device*,struct uinput_request*) ; 

__attribute__((used)) static int uinput_dev_upload_effect(struct input_dev *dev,
				    struct ff_effect *effect,
				    struct ff_effect *old)
{
	struct uinput_device *udev = input_get_drvdata(dev);
	struct uinput_request request;

	/*
	 * uinput driver does not currently support periodic effects with
	 * custom waveform since it does not have a way to pass buffer of
	 * samples (custom_data) to userspace. If ever there is a device
	 * supporting custom waveforms we would need to define an additional
	 * ioctl (UI_UPLOAD_SAMPLES) but for now we just bail out.
	 */
	if (effect->type == FF_PERIODIC &&
			effect->u.periodic.waveform == FF_CUSTOM)
		return -EINVAL;

	request.code = UI_FF_UPLOAD;
	request.u.upload.effect = effect;
	request.u.upload.old = old;

	return uinput_request_submit(udev, &request);
}