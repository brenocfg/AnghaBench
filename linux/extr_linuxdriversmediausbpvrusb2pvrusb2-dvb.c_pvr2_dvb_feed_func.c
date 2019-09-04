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
struct pvr2_stream {int dummy; } ;
struct TYPE_4__ {TYPE_1__* stream; } ;
struct pvr2_dvb_adapter {int /*<<< orphan*/  buffer_wait_data; int /*<<< orphan*/ * buffer_storage; int /*<<< orphan*/  demux; TYPE_2__ channel; } ;
struct pvr2_buffer {int dummy; } ;
struct TYPE_3__ {struct pvr2_stream* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_DVB_FEED ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ kthread_should_stop () ; 
 unsigned int pvr2_buffer_get_count (struct pvr2_buffer*) ; 
 size_t pvr2_buffer_get_id (struct pvr2_buffer*) ; 
 int pvr2_buffer_get_status (struct pvr2_buffer*) ; 
 int pvr2_buffer_queue (struct pvr2_buffer*) ; 
 struct pvr2_buffer* pvr2_stream_get_ready_buffer (struct pvr2_stream*) ; 
 scalar_t__ pvr2_stream_get_ready_count (struct pvr2_stream*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pvr2_dvb_feed_func(struct pvr2_dvb_adapter *adap)
{
	int ret;
	unsigned int count;
	struct pvr2_buffer *bp;
	struct pvr2_stream *stream;

	pvr2_trace(PVR2_TRACE_DVB_FEED, "dvb feed thread started");
	set_freezable();

	stream = adap->channel.stream->stream;

	for (;;) {
		if (kthread_should_stop()) break;

		/* Not sure about this... */
		try_to_freeze();

		bp = pvr2_stream_get_ready_buffer(stream);
		if (bp != NULL) {
			count = pvr2_buffer_get_count(bp);
			if (count) {
				dvb_dmx_swfilter(
					&adap->demux,
					adap->buffer_storage[
					    pvr2_buffer_get_id(bp)],
					count);
			} else {
				ret = pvr2_buffer_get_status(bp);
				if (ret < 0) break;
			}
			ret = pvr2_buffer_queue(bp);
			if (ret < 0) break;

			/* Since we know we did something to a buffer,
			   just go back and try again.  No point in
			   blocking unless we really ran out of
			   buffers to process. */
			continue;
		}


		/* Wait until more buffers become available or we're
		   told not to wait any longer. */
		ret = wait_event_interruptible(
		    adap->buffer_wait_data,
		    (pvr2_stream_get_ready_count(stream) > 0) ||
		    kthread_should_stop());
		if (ret < 0) break;
	}

	/* If we get here and ret is < 0, then an error has occurred.
	   Probably would be a good idea to communicate that to DVB core... */

	pvr2_trace(PVR2_TRACE_DVB_FEED, "dvb feed thread stopped");

	return 0;
}