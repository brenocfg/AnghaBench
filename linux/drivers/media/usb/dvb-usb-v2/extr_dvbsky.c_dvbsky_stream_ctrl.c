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
typedef  int u8 ;
struct dvbsky_state {int /*<<< orphan*/  stream_mutex; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 struct dvbsky_state* d_to_priv (struct dvb_usb_device*) ; 
 int dvbsky_usb_generic_rw (struct dvb_usb_device*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvbsky_stream_ctrl(struct dvb_usb_device *d, u8 onoff)
{
	struct dvbsky_state *state = d_to_priv(d);
	int ret;
	u8 obuf_pre[3] = { 0x37, 0, 0 };
	u8 obuf_post[3] = { 0x36, 3, 0 };

	mutex_lock(&state->stream_mutex);
	ret = dvbsky_usb_generic_rw(d, obuf_pre, 3, NULL, 0);
	if (!ret && onoff) {
		msleep(20);
		ret = dvbsky_usb_generic_rw(d, obuf_post, 3, NULL, 0);
	}
	mutex_unlock(&state->stream_mutex);
	return ret;
}