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
typedef  scalar_t__ u32 ;
struct hv_ring_buffer_info {scalar_t__ ring_datasize; TYPE_1__* ring_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  write_index; int /*<<< orphan*/  read_index; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hv_get_ringbuffer_availbytes(const struct hv_ring_buffer_info *rbi,
			     u32 *read, u32 *write)
{
	u32 read_loc, write_loc, dsize;

	/* Capture the read/write indices before they changed */
	read_loc = READ_ONCE(rbi->ring_buffer->read_index);
	write_loc = READ_ONCE(rbi->ring_buffer->write_index);
	dsize = rbi->ring_datasize;

	*write = write_loc >= read_loc ? dsize - (write_loc - read_loc) :
		read_loc - write_loc;
	*read = dsize - *write;
}