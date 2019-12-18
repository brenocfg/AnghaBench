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
struct visorchannel {int /*<<< orphan*/  chan_hdr; } ;
struct signal_queue_header {int /*<<< orphan*/  signal_size; } ;

/* Variables and functions */
 int sig_data_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct signal_queue_header*,int /*<<< orphan*/ ) ; 
 int visorchannel_write (struct visorchannel*,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sig_write_data(struct visorchannel *channel, u32 queue,
			  struct signal_queue_header *sig_hdr, u32 slot,
			  void *data)
{
	int signal_data_offset = sig_data_offset(&channel->chan_hdr, queue,
						 sig_hdr, slot);

	return visorchannel_write(channel, signal_data_offset,
				  data, sig_hdr->signal_size);
}