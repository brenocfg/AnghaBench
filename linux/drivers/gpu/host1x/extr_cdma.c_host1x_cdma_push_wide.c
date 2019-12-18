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
typedef  int /*<<< orphan*/  u32 ;
struct push_buffer {scalar_t__ pos; scalar_t__ size; } ;
struct host1x_channel {int /*<<< orphan*/  dev; } ;
struct host1x_cdma {unsigned int slots_free; unsigned int slots_used; struct push_buffer push_buffer; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 struct host1x_channel* cdma_to_channel (struct host1x_cdma*) ; 
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_cdma_wait_pushbuffer_space (struct host1x*,struct host1x_cdma*,unsigned int) ; 
 scalar_t__ host1x_debug_trace_cmdbuf ; 
 int /*<<< orphan*/  host1x_pushbuffer_push (struct push_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int host1x_pushbuffer_space (struct push_buffer*) ; 
 int /*<<< orphan*/  trace_host1x_cdma_push_wide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void host1x_cdma_push_wide(struct host1x_cdma *cdma, u32 op1, u32 op2,
			   u32 op3, u32 op4)
{
	struct host1x_channel *channel = cdma_to_channel(cdma);
	struct host1x *host1x = cdma_to_host1x(cdma);
	struct push_buffer *pb = &cdma->push_buffer;
	unsigned int needed = 2, extra = 0, i;
	unsigned int space = cdma->slots_free;

	if (host1x_debug_trace_cmdbuf)
		trace_host1x_cdma_push_wide(dev_name(channel->dev), op1, op2,
					    op3, op4);

	/* compute number of extra slots needed for padding */
	if (pb->pos + 16 > pb->size) {
		extra = (pb->size - pb->pos) / 8;
		needed += extra;
	}

	host1x_cdma_wait_pushbuffer_space(host1x, cdma, needed);
	space = host1x_pushbuffer_space(pb);

	cdma->slots_free = space - needed;
	cdma->slots_used += needed;

	/*
	 * Note that we rely on the fact that this is only used to submit wide
	 * gather opcodes, which consist of 3 words, and they are padded with
	 * a NOP to avoid having to deal with fractional slots (a slot always
	 * represents 2 words). The fourth opcode passed to this function will
	 * therefore always be a NOP.
	 *
	 * This works around a slight ambiguity when it comes to opcodes. For
	 * all current host1x incarnations the NOP opcode uses the exact same
	 * encoding (0x20000000), so we could hard-code the value here, but a
	 * new incarnation may change it and break that assumption.
	 */
	for (i = 0; i < extra; i++)
		host1x_pushbuffer_push(pb, op4, op4);

	host1x_pushbuffer_push(pb, op1, op2);
	host1x_pushbuffer_push(pb, op3, op4);
}