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
typedef  void* u32 ;
struct hv_ring_buffer_info {int /*<<< orphan*/  ring_buffer_mutex; TYPE_1__* ring_buffer; } ;
struct hv_ring_buffer_debug_info {int /*<<< orphan*/  current_interrupt_mask; int /*<<< orphan*/  current_write_index; int /*<<< orphan*/  current_read_index; void* bytes_avail_towrite; void* bytes_avail_toread; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_mask; int /*<<< orphan*/  write_index; int /*<<< orphan*/  read_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hv_get_ringbuffer_availbytes (struct hv_ring_buffer_info*,void**,void**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hv_ringbuffer_get_debuginfo(struct hv_ring_buffer_info *ring_info,
				struct hv_ring_buffer_debug_info *debug_info)
{
	u32 bytes_avail_towrite;
	u32 bytes_avail_toread;

	mutex_lock(&ring_info->ring_buffer_mutex);

	if (!ring_info->ring_buffer) {
		mutex_unlock(&ring_info->ring_buffer_mutex);
		return -EINVAL;
	}

	hv_get_ringbuffer_availbytes(ring_info,
				     &bytes_avail_toread,
				     &bytes_avail_towrite);
	debug_info->bytes_avail_toread = bytes_avail_toread;
	debug_info->bytes_avail_towrite = bytes_avail_towrite;
	debug_info->current_read_index = ring_info->ring_buffer->read_index;
	debug_info->current_write_index = ring_info->ring_buffer->write_index;
	debug_info->current_interrupt_mask
		= ring_info->ring_buffer->interrupt_mask;
	mutex_unlock(&ring_info->ring_buffer_mutex);

	return 0;
}