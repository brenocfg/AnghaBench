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
struct pvr2_ioread {int sync_state; int spigot_open; int /*<<< orphan*/  stream; scalar_t__ stream_running; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int BUFFER_COUNT ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  PVR2_TRACE_DATA_FLOW ; 
 int /*<<< orphan*/  pvr2_ioread_filter (struct pvr2_ioread*) ; 
 int pvr2_stream_get_ready_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,char*) ; 

int pvr2_ioread_avail(struct pvr2_ioread *cp)
{
	int ret;
	if (!(cp->enabled)) {
		// Stream is not enabled; so this is an I/O error
		return -EIO;
	}

	if (cp->sync_state == 1) {
		pvr2_ioread_filter(cp);
		if (cp->sync_state == 1) return -EAGAIN;
	}

	ret = 0;
	if (cp->stream_running) {
		if (!pvr2_stream_get_ready_count(cp->stream)) {
			// No data available at all right now.
			ret = -EAGAIN;
		}
	} else {
		if (pvr2_stream_get_ready_count(cp->stream) < BUFFER_COUNT/2) {
			// Haven't buffered up enough yet; try again later
			ret = -EAGAIN;
		}
	}

	if ((!(cp->spigot_open)) != (!(ret == 0))) {
		cp->spigot_open = (ret == 0);
		pvr2_trace(PVR2_TRACE_DATA_FLOW,
			   "/*---TRACE_READ---*/ data is %s",
			   cp->spigot_open ? "available" : "pending");
	}

	return ret;
}