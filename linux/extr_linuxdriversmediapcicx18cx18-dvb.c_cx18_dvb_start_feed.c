#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dvb_demux_feed {int /*<<< orphan*/  index; int /*<<< orphan*/  pid; struct dvb_demux* demux; } ;
struct TYPE_5__ {int /*<<< orphan*/  frontend; } ;
struct dvb_demux {TYPE_2__ dmx; scalar_t__ priv; } ;
struct cx18_stream {TYPE_3__* dvb; int /*<<< orphan*/  s_flags; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; TYPE_1__* card; } ;
struct TYPE_6__ {scalar_t__ feeding; int /*<<< orphan*/  feedlock; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
#define  CX18_CARD_GOTVIEW_PCI_DVD3 133 
#define  CX18_CARD_HVR_1600_ESMT 132 
#define  CX18_CARD_HVR_1600_S5H1411 131 
#define  CX18_CARD_HVR_1600_SAMSUNG 130 
#define  CX18_CARD_LEADTEK_DVR3100H 129 
#define  CX18_CARD_YUAN_MPC718 128 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  CX18_ERR (char*) ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_REG_DMUX_NUM_PORT_0_CONTROL ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cx18_init_on_first_open (struct cx18*) ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int cx18_start_v4l2_encode_stream (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx18_dvb_start_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct cx18_stream *stream = (struct cx18_stream *) demux->priv;
	struct cx18 *cx;
	int ret;
	u32 v;

	if (!stream)
		return -EINVAL;

	cx = stream->cx;
	CX18_DEBUG_INFO("Start feed: pid = 0x%x index = %d\n",
			feed->pid, feed->index);

	mutex_lock(&cx->serialize_lock);
	ret = cx18_init_on_first_open(cx);
	mutex_unlock(&cx->serialize_lock);
	if (ret) {
		CX18_ERR("Failed to initialize firmware starting DVB feed\n");
		return ret;
	}
	ret = -EINVAL;

	switch (cx->card->type) {
	case CX18_CARD_HVR_1600_ESMT:
	case CX18_CARD_HVR_1600_SAMSUNG:
	case CX18_CARD_HVR_1600_S5H1411:
		v = cx18_read_reg(cx, CX18_REG_DMUX_NUM_PORT_0_CONTROL);
		v |= 0x00400000; /* Serial Mode */
		v |= 0x00002000; /* Data Length - Byte */
		v |= 0x00010000; /* Error - Polarity */
		v |= 0x00020000; /* Error - Passthru */
		v |= 0x000c0000; /* Error - Ignore */
		cx18_write_reg(cx, v, CX18_REG_DMUX_NUM_PORT_0_CONTROL);
		break;

	case CX18_CARD_LEADTEK_DVR3100H:
	case CX18_CARD_YUAN_MPC718:
	case CX18_CARD_GOTVIEW_PCI_DVD3:
	default:
		/* Assumption - Parallel transport - Signalling
		 * undefined or default.
		 */
		break;
	}

	if (!demux->dmx.frontend)
		return -EINVAL;

	mutex_lock(&stream->dvb->feedlock);
	if (stream->dvb->feeding++ == 0) {
		CX18_DEBUG_INFO("Starting Transport DMA\n");
		mutex_lock(&cx->serialize_lock);
		set_bit(CX18_F_S_STREAMING, &stream->s_flags);
		ret = cx18_start_v4l2_encode_stream(stream);
		if (ret < 0) {
			CX18_DEBUG_INFO("Failed to start Transport DMA\n");
			stream->dvb->feeding--;
			if (stream->dvb->feeding == 0)
				clear_bit(CX18_F_S_STREAMING, &stream->s_flags);
		}
		mutex_unlock(&cx->serialize_lock);
	} else
		ret = 0;
	mutex_unlock(&stream->dvb->feedlock);

	return ret;
}