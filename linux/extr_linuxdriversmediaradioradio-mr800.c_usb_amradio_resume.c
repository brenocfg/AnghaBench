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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct amradio_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  muted; int /*<<< orphan*/  curfreq; int /*<<< orphan*/  stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amradio_set_freq (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amradio_set_mute (struct amradio_device*,int) ; 
 int /*<<< orphan*/  amradio_set_stereo (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct amradio_device* to_amradio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int usb_amradio_resume(struct usb_interface *intf)
{
	struct amradio_device *radio = to_amradio_dev(usb_get_intfdata(intf));

	mutex_lock(&radio->lock);
	amradio_set_stereo(radio, radio->stereo);
	amradio_set_freq(radio, radio->curfreq);

	if (!radio->muted)
		amradio_set_mute(radio, false);

	mutex_unlock(&radio->lock);

	dev_info(&intf->dev, "coming out of suspend..\n");
	return 0;
}