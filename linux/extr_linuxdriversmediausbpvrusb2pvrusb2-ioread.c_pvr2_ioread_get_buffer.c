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
struct pvr2_ioread {scalar_t__ c_data_len; scalar_t__ c_data_offs; int /*<<< orphan*/ * c_buf; int /*<<< orphan*/ ** buffer_storage; int /*<<< orphan*/ * c_data_ptr; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_DATA_FLOW ; 
 scalar_t__ pvr2_buffer_get_count (int /*<<< orphan*/ *) ; 
 size_t pvr2_buffer_get_id (int /*<<< orphan*/ *) ; 
 int pvr2_buffer_get_status (int /*<<< orphan*/ *) ; 
 int pvr2_buffer_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_ioread_stop (struct pvr2_ioread*) ; 
 int /*<<< orphan*/ * pvr2_stream_get_ready_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_ioread*,int) ; 

__attribute__((used)) static int pvr2_ioread_get_buffer(struct pvr2_ioread *cp)
{
	int stat;

	while (cp->c_data_len <= cp->c_data_offs) {
		if (cp->c_buf) {
			// Flush out current buffer first.
			stat = pvr2_buffer_queue(cp->c_buf);
			if (stat < 0) {
				// Streaming error...
				pvr2_trace(PVR2_TRACE_DATA_FLOW,
					   "/*---TRACE_READ---*/ pvr2_ioread_read id=%p queue_error=%d",
					   cp,stat);
				pvr2_ioread_stop(cp);
				return 0;
			}
			cp->c_buf = NULL;
			cp->c_data_ptr = NULL;
			cp->c_data_len = 0;
			cp->c_data_offs = 0;
		}
		// Now get a freshly filled buffer.
		cp->c_buf = pvr2_stream_get_ready_buffer(cp->stream);
		if (!cp->c_buf) break; // Nothing ready; done.
		cp->c_data_len = pvr2_buffer_get_count(cp->c_buf);
		if (!cp->c_data_len) {
			// Nothing transferred.  Was there an error?
			stat = pvr2_buffer_get_status(cp->c_buf);
			if (stat < 0) {
				// Streaming error...
				pvr2_trace(PVR2_TRACE_DATA_FLOW,
					   "/*---TRACE_READ---*/ pvr2_ioread_read id=%p buffer_error=%d",
					   cp,stat);
				pvr2_ioread_stop(cp);
				// Give up.
				return 0;
			}
			// Start over...
			continue;
		}
		cp->c_data_offs = 0;
		cp->c_data_ptr = cp->buffer_storage[
			pvr2_buffer_get_id(cp->c_buf)];
	}
	return !0;
}