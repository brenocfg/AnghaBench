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
struct dvb_usb_adapter {TYPE_2__* dev; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct cxusb_state {int (* fe_read_status ) (struct dvb_frontend*,int*) ;int last_lock; int /*<<< orphan*/  stream_mutex; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_4__ {scalar_t__ priv; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 int /*<<< orphan*/  cxusb_streaming_ctrl (struct dvb_usb_adapter*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int cxusb_read_status(struct dvb_frontend *fe,
				  enum fe_status *status)
{
	struct dvb_usb_adapter *adap = (struct dvb_usb_adapter *)fe->dvb->priv;
	struct cxusb_state *state = (struct cxusb_state *)adap->dev->priv;
	int ret;

	ret = state->fe_read_status(fe, status);

	/* it need resync slave fifo when signal change from unlock to lock.*/
	if ((*status & FE_HAS_LOCK) && (!state->last_lock)) {
		mutex_lock(&state->stream_mutex);
		cxusb_streaming_ctrl(adap, 1);
		mutex_unlock(&state->stream_mutex);
	}

	state->last_lock = (*status & FE_HAS_LOCK) ? 1 : 0;
	return ret;
}