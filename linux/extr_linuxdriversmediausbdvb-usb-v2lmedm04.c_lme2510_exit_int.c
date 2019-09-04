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
struct lme2510_state {int i2c_talk_onoff; TYPE_1__* lme_urb; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * usb_buffer; scalar_t__ signal_sn; scalar_t__ signal_level; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; struct dvb_usb_adapter* adapter; struct lme2510_state* priv; } ;
struct dvb_usb_adapter {int /*<<< orphan*/  stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  lme2510_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 

__attribute__((used)) static void *lme2510_exit_int(struct dvb_usb_device *d)
{
	struct lme2510_state *st = d->priv;
	struct dvb_usb_adapter *adap = &d->adapter[0];
	void *buffer = NULL;

	if (adap != NULL) {
		lme2510_kill_urb(&adap->stream);
	}

	if (st->usb_buffer != NULL) {
		st->i2c_talk_onoff = 1;
		st->signal_level = 0;
		st->signal_sn = 0;
		buffer = st->usb_buffer;
	}

	if (st->lme_urb != NULL) {
		usb_kill_urb(st->lme_urb);
		usb_free_coherent(d->udev, 128, st->buffer,
				  st->lme_urb->transfer_dma);
		info("Interrupt Service Stopped");
	}

	return buffer;
}