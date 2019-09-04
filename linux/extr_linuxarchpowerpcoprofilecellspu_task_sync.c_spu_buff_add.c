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
struct TYPE_2__ {size_t head; size_t tail; unsigned long* buff; } ;

/* Variables and functions */
 int max_spu_buff ; 
 int /*<<< orphan*/  oprofile_cpu_buffer_inc_smpl_lost () ; 
 TYPE_1__* spu_buff ; 

__attribute__((used)) static void spu_buff_add(unsigned long int value, int spu)
{
	/* spu buff is a circular buffer.  Add entries to the
	 * head.  Head is the index to store the next value.
	 * The buffer is full when there is one available entry
	 * in the queue, i.e. head and tail can't be equal.
	 * That way we can tell the difference between the
	 * buffer being full versus empty.
	 *
	 *  ASSUMPTION: the buffer_lock is held when this function
	 *             is called to lock the buffer, head and tail.
	 */
	int full = 1;

	if (spu_buff[spu].head >= spu_buff[spu].tail) {
		if ((spu_buff[spu].head - spu_buff[spu].tail)
		    <  (max_spu_buff - 1))
			full = 0;

	} else if (spu_buff[spu].tail > spu_buff[spu].head) {
		if ((spu_buff[spu].tail - spu_buff[spu].head)
		    > 1)
			full = 0;
	}

	if (!full) {
		spu_buff[spu].buff[spu_buff[spu].head] = value;
		spu_buff[spu].head++;

		if (spu_buff[spu].head >= max_spu_buff)
			spu_buff[spu].head = 0;
	} else {
		/* From the user's perspective make the SPU buffer
		 * size management/overflow look like we are using
		 * per cpu buffers.  The user uses the same
		 * per cpu parameter to adjust the SPU buffer size.
		 * Increment the sample_lost_overflow to inform
		 * the user the buffer size needs to be increased.
		 */
		oprofile_cpu_buffer_inc_smpl_lost();
	}
}