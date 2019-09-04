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
struct dvbsky_state {scalar_t__ last_lock; int /*<<< orphan*/  stream_mutex; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 struct dvbsky_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvbsky_init(struct dvb_usb_device *d)
{
	struct dvbsky_state *state = d_to_priv(d);

	/* use default interface */
	/*
	ret = usb_set_interface(d->udev, 0, 0);
	if (ret)
		return ret;
	*/
	mutex_init(&state->stream_mutex);

	state->last_lock = 0;

	return 0;
}