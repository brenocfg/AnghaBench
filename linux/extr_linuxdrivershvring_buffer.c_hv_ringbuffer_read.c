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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct vmpacket_descriptor {int offset8; int len8; int /*<<< orphan*/  trans_id; } ;
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  __hv_pkt_iter_next (struct vmbus_channel*,struct vmpacket_descriptor*) ; 
 int /*<<< orphan*/  hv_pkt_iter_close (struct vmbus_channel*) ; 
 struct vmpacket_descriptor* hv_pkt_iter_first (struct vmbus_channel*) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 scalar_t__ unlikely (int) ; 

int hv_ringbuffer_read(struct vmbus_channel *channel,
		       void *buffer, u32 buflen, u32 *buffer_actual_len,
		       u64 *requestid, bool raw)
{
	struct vmpacket_descriptor *desc;
	u32 packetlen, offset;

	if (unlikely(buflen == 0))
		return -EINVAL;

	*buffer_actual_len = 0;
	*requestid = 0;

	/* Make sure there is something to read */
	desc = hv_pkt_iter_first(channel);
	if (desc == NULL) {
		/*
		 * No error is set when there is even no header, drivers are
		 * supposed to analyze buffer_actual_len.
		 */
		return 0;
	}

	offset = raw ? 0 : (desc->offset8 << 3);
	packetlen = (desc->len8 << 3) - offset;
	*buffer_actual_len = packetlen;
	*requestid = desc->trans_id;

	if (unlikely(packetlen > buflen))
		return -ENOBUFS;

	/* since ring is double mapped, only one copy is necessary */
	memcpy(buffer, (const char *)desc + offset, packetlen);

	/* Advance ring index to next packet descriptor */
	__hv_pkt_iter_next(channel, desc);

	/* Notify host of update */
	hv_pkt_iter_close(channel);

	return 0;
}