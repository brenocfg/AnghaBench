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
struct push_buffer {int dummy; } ;
struct host1x_cdma {scalar_t__ slots_free; int /*<<< orphan*/  slots_used; struct push_buffer push_buffer; } ;
struct host1x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDMA_EVENT_PUSH_BUFFER_SPACE ; 
 TYPE_1__* cdma_to_channel (struct host1x_cdma*) ; 
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ host1x_cdma_wait_locked (struct host1x_cdma*,int /*<<< orphan*/ ) ; 
 scalar_t__ host1x_debug_trace_cmdbuf ; 
 int /*<<< orphan*/  host1x_hw_cdma_flush (struct host1x*,struct host1x_cdma*) ; 
 int /*<<< orphan*/  host1x_pushbuffer_push (struct push_buffer*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_host1x_cdma_push (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void host1x_cdma_push(struct host1x_cdma *cdma, u32 op1, u32 op2)
{
	struct host1x *host1x = cdma_to_host1x(cdma);
	struct push_buffer *pb = &cdma->push_buffer;
	u32 slots_free = cdma->slots_free;

	if (host1x_debug_trace_cmdbuf)
		trace_host1x_cdma_push(dev_name(cdma_to_channel(cdma)->dev),
				       op1, op2);

	if (slots_free == 0) {
		host1x_hw_cdma_flush(host1x, cdma);
		slots_free = host1x_cdma_wait_locked(cdma,
						CDMA_EVENT_PUSH_BUFFER_SPACE);
	}

	cdma->slots_free = slots_free - 1;
	cdma->slots_used++;
	host1x_pushbuffer_push(pb, op1, op2);
}