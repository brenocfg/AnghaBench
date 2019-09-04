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
struct rchan_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ relay_buf_full (struct rchan_buf*) ; 

__attribute__((used)) static int subbuf_start_callback(struct rchan_buf *buf,
				 void *subbuf,
				 void *prev_subbuf,
				 size_t prev_padding)
{
	/*
	 * Use no-overwrite mode by default, where relay will stop accepting
	 * new data if there are no empty sub buffers left.
	 * There is no strict synchronization enforced by relay between Consumer
	 * and Producer. In overwrite mode, there is a possibility of getting
	 * inconsistent/garbled data, the producer could be writing on to the
	 * same sub buffer from which Consumer is reading. This can't be avoided
	 * unless Consumer is fast enough and can always run in tandem with
	 * Producer.
	 */
	if (relay_buf_full(buf))
		return 0;

	return 1;
}