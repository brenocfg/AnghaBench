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
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int __vmbus_open (struct vmbus_channel*,void*,int /*<<< orphan*/ ,void (*) (void*),void*) ; 
 int vmbus_alloc_ring (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_free_ring (struct vmbus_channel*) ; 

int vmbus_open(struct vmbus_channel *newchannel,
	       u32 send_ringbuffer_size, u32 recv_ringbuffer_size,
	       void *userdata, u32 userdatalen,
	       void (*onchannelcallback)(void *context), void *context)
{
	int err;

	err = vmbus_alloc_ring(newchannel, send_ringbuffer_size,
			       recv_ringbuffer_size);
	if (err)
		return err;

	err = __vmbus_open(newchannel, userdata, userdatalen,
			   onchannelcallback, context);
	if (err)
		vmbus_free_ring(newchannel);

	return err;
}