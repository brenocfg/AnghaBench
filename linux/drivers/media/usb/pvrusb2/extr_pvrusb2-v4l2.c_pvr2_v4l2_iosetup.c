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
struct TYPE_9__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {scalar_t__ rhp; TYPE_2__* pdi; TYPE_4__ channel; } ;
struct pvr2_stream {int dummy; } ;
struct pvr2_hdw {int dummy; } ;
typedef  int /*<<< orphan*/  pvr2_stream_callback ;
struct TYPE_8__ {struct pvr2_stream* stream; } ;
struct TYPE_7__ {int /*<<< orphan*/  config; TYPE_3__* stream; } ;
struct TYPE_6__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int pvr2_channel_claim_stream (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ pvr2_channel_create_mpeg_stream (TYPE_3__*) ; 
 int /*<<< orphan*/  pvr2_hdw_set_stream_type (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int pvr2_hdw_set_streaming (struct pvr2_hdw*,int) ; 
 int pvr2_ioread_set_enabled (scalar_t__,int) ; 
 int /*<<< orphan*/  pvr2_stream_set_callback (struct pvr2_stream*,int /*<<< orphan*/ ,struct pvr2_v4l2_fh*) ; 
 scalar_t__ pvr2_v4l2_notify ; 

__attribute__((used)) static int pvr2_v4l2_iosetup(struct pvr2_v4l2_fh *fh)
{
	int ret;
	struct pvr2_stream *sp;
	struct pvr2_hdw *hdw;
	if (fh->rhp) return 0;

	if (!fh->pdi->stream) {
		/* No stream defined for this node.  This means that we're
		   not currently allowed to stream from this node. */
		return -EPERM;
	}

	/* First read() attempt.  Try to claim the stream and start
	   it... */
	if ((ret = pvr2_channel_claim_stream(&fh->channel,
					     fh->pdi->stream)) != 0) {
		/* Someone else must already have it */
		return ret;
	}

	fh->rhp = pvr2_channel_create_mpeg_stream(fh->pdi->stream);
	if (!fh->rhp) {
		pvr2_channel_claim_stream(&fh->channel,NULL);
		return -ENOMEM;
	}

	hdw = fh->channel.mc_head->hdw;
	sp = fh->pdi->stream->stream;
	pvr2_stream_set_callback(sp,(pvr2_stream_callback)pvr2_v4l2_notify,fh);
	pvr2_hdw_set_stream_type(hdw,fh->pdi->config);
	if ((ret = pvr2_hdw_set_streaming(hdw,!0)) < 0) return ret;
	return pvr2_ioread_set_enabled(fh->rhp,!0);
}