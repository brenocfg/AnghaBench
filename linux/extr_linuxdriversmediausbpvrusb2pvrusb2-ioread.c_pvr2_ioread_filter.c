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
struct pvr2_ioread {int sync_state; unsigned int c_data_len; unsigned int c_data_offs; size_t sync_buf_offs; size_t sync_key_len; scalar_t__* c_data_ptr; scalar_t__* sync_key_ptr; unsigned int sync_trashed_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_DATA_FLOW ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_ioread_get_buffer (struct pvr2_ioread*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,unsigned int,...) ; 

__attribute__((used)) static void pvr2_ioread_filter(struct pvr2_ioread *cp)
{
	unsigned int idx;
	if (!cp->enabled) return;
	if (cp->sync_state != 1) return;

	// Search the stream for our synchronization key.  This is made
	// complicated by the fact that in order to be honest with
	// ourselves here we must search across buffer boundaries...
	mutex_lock(&cp->mutex);
	while (1) {
		// Ensure we have a buffer
		if (!pvr2_ioread_get_buffer(cp)) break;
		if (!cp->c_data_len) break;

		// Now walk the buffer contents until we match the key or
		// run out of buffer data.
		for (idx = cp->c_data_offs; idx < cp->c_data_len; idx++) {
			if (cp->sync_buf_offs >= cp->sync_key_len) break;
			if (cp->c_data_ptr[idx] ==
			    cp->sync_key_ptr[cp->sync_buf_offs]) {
				// Found the next key byte
				(cp->sync_buf_offs)++;
			} else {
				// Whoops, mismatched.  Start key over...
				cp->sync_buf_offs = 0;
			}
		}

		// Consume what we've walked through
		cp->c_data_offs += idx;
		cp->sync_trashed_count += idx;

		// If we've found the key, then update state and get out.
		if (cp->sync_buf_offs >= cp->sync_key_len) {
			cp->sync_trashed_count -= cp->sync_key_len;
			pvr2_trace(PVR2_TRACE_DATA_FLOW,
				   "/*---TRACE_READ---*/ sync_state <== 2 (skipped %u bytes)",
				   cp->sync_trashed_count);
			cp->sync_state = 2;
			cp->sync_buf_offs = 0;
			break;
		}

		if (cp->c_data_offs < cp->c_data_len) {
			// Sanity check - should NEVER get here
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "ERROR: pvr2_ioread filter sync problem len=%u offs=%u",
				   cp->c_data_len,cp->c_data_offs);
			// Get out so we don't get stuck in an infinite
			// loop.
			break;
		}

		continue; // (for clarity)
	}
	mutex_unlock(&cp->mutex);
}