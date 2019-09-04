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
typedef  int /*<<< orphan*/  u8 ;
struct lme2510_state {int i2c_talk_onoff; } ;
struct dvb_usb_device {struct lme2510_state* priv; } ;

/* Variables and functions */
 int lme2510_usb_talk (struct dvb_usb_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lme2510_msg(struct dvb_usb_device *d,
		u8 *wbuf, int wlen, u8 *rbuf, int rlen)
{
	struct lme2510_state *st = d->priv;

	st->i2c_talk_onoff = 1;

	return lme2510_usb_talk(d, wbuf, wlen, rbuf, rlen);
}