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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct amradio_device {TYPE_1__ vdev; int /*<<< orphan*/  curfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  amradio_dev_err (int /*<<< orphan*/ *,char*) ; 
 int amradio_set_freq (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int amradio_set_mute (struct amradio_device*,int) ; 
 int amradio_set_stereo (struct amradio_device*,int) ; 

__attribute__((used)) static int usb_amradio_init(struct amradio_device *radio)
{
	int retval;

	retval = amradio_set_mute(radio, true);
	if (retval)
		goto out_err;
	retval = amradio_set_stereo(radio, true);
	if (retval)
		goto out_err;
	retval = amradio_set_freq(radio, radio->curfreq);
	if (retval)
		goto out_err;
	return 0;

out_err:
	amradio_dev_err(&radio->vdev.dev, "initialization failed\n");
	return retval;
}