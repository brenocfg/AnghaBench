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
struct lcs_channel {TYPE_1__* ccws; struct lcs_buffer* iob; } ;
struct lcs_buffer {scalar_t__ state; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CCW_FLAG_PCI ; 
 int /*<<< orphan*/  CCW_FLAG_SUSPEND ; 
 scalar_t__ LCS_BUF_STATE_PROCESSED ; 
 scalar_t__ LCS_BUF_STATE_READY ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int LCS_NUM_BUFFS ; 
 int /*<<< orphan*/  __lcs_ready_buffer_bits (struct lcs_channel*,int) ; 
 int __lcs_resume_channel (struct lcs_channel*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
__lcs_processed_buffer(struct lcs_channel *channel, struct lcs_buffer *buffer)
{
	int index, prev, next;

	LCS_DBF_TEXT(5, trace, "prcsbuff");
	BUG_ON(buffer->state != LCS_BUF_STATE_READY);
	buffer->state = LCS_BUF_STATE_PROCESSED;
	index = buffer - channel->iob;
	prev = (index - 1) & (LCS_NUM_BUFFS - 1);
	next = (index + 1) & (LCS_NUM_BUFFS - 1);
	/* Set the suspend bit and clear the PCI bit of this buffer. */
	channel->ccws[index].flags |= CCW_FLAG_SUSPEND;
	channel->ccws[index].flags &= ~CCW_FLAG_PCI;
	/* Check the suspend bit of the previous buffer. */
	if (channel->iob[prev].state == LCS_BUF_STATE_READY) {
		/*
		 * Previous buffer is in state ready. It might have
		 * happened in lcs_ready_buffer that the suspend bit
		 * has not been cleared to avoid an endless loop.
		 * Do it now.
		 */
		__lcs_ready_buffer_bits(channel, prev);
	}
	/* Clear PCI bit of next buffer. */
	channel->ccws[next].flags &= ~CCW_FLAG_PCI;
	return __lcs_resume_channel(channel);
}