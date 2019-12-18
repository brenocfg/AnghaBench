#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {int id; TYPE_4__* dev; TYPE_3__* fe_adap; } ;
struct dib0700_state {int fw_version; int* buf; int disable_streaming_master_mode; int channel_state; int /*<<< orphan*/  nb_packet_buffer_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  usb_mutex; struct dib0700_state* priv; } ;
struct TYPE_6__ {int endpoint; } ;
struct TYPE_7__ {TYPE_1__ props; } ;
struct TYPE_8__ {TYPE_2__ stream; } ;

/* Variables and functions */
 int REQUEST_ENABLE_VIDEO ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 
 int dib0700_ctrl_wr (TYPE_4__*,int*,int) ; 
 int dib0700_set_usb_xfer_len (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dib0700_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	struct dib0700_state *st = adap->dev->priv;
	int ret;

	if ((onoff != 0) && (st->fw_version >= 0x10201)) {
		/* for firmware later than 1.20.1,
		 * the USB xfer length can be set  */
		ret = dib0700_set_usb_xfer_len(adap->dev,
			st->nb_packet_buffer_size);
		if (ret < 0) {
			deb_info("can not set the USB xfer len\n");
			return ret;
		}
	}

	mutex_lock(&adap->dev->usb_mutex);

	st->buf[0] = REQUEST_ENABLE_VIDEO;
	/* this bit gives a kind of command,
	 * rather than enabling something or not */
	st->buf[1] = (onoff << 4) | 0x00;

	if (st->disable_streaming_master_mode == 1)
		st->buf[2] = 0x00;
	else
		st->buf[2] = 0x01 << 4; /* Master mode */

	st->buf[3] = 0x00;

	deb_info("modifying (%d) streaming state for %d\n", onoff, adap->id);

	st->channel_state &= ~0x3;
	if ((adap->fe_adap[0].stream.props.endpoint != 2)
			&& (adap->fe_adap[0].stream.props.endpoint != 3)) {
		deb_info("the endpoint number (%i) is not correct, use the adapter id instead", adap->fe_adap[0].stream.props.endpoint);
		if (onoff)
			st->channel_state |=	1 << (adap->id);
		else
			st->channel_state |=	1 << ~(adap->id);
	} else {
		if (onoff)
			st->channel_state |=	1 << (adap->fe_adap[0].stream.props.endpoint-2);
		else
			st->channel_state |=	1 << (3-adap->fe_adap[0].stream.props.endpoint);
	}

	st->buf[2] |= st->channel_state;

	deb_info("data for streaming: %x %x\n", st->buf[1], st->buf[2]);

	ret = dib0700_ctrl_wr(adap->dev, st->buf, 4);
	mutex_unlock(&adap->dev->usb_mutex);

	return ret;
}