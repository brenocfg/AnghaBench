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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ch_space_offset; } ;
struct visorchannel {TYPE_1__ chan_hdr; } ;
struct signal_queue_header {int dummy; } ;
struct channel_header {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  sig_queue_offset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int visorchannel_read (struct visorchannel*,int /*<<< orphan*/ ,struct signal_queue_header*,int) ; 

__attribute__((used)) static int sig_read_header(struct visorchannel *channel, u32 queue,
			   struct signal_queue_header *sig_hdr)
{
	if (channel->chan_hdr.ch_space_offset < sizeof(struct channel_header))
		return -EINVAL;

	/* Read the appropriate SIGNAL_QUEUE_HEADER into local memory. */
	return visorchannel_read(channel,
				 sig_queue_offset(&channel->chan_hdr, queue),
				 sig_hdr, sizeof(struct signal_queue_header));
}