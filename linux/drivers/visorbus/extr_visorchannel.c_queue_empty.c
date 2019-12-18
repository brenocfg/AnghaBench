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
struct visorchannel {int dummy; } ;
struct signal_queue_header {scalar_t__ head; scalar_t__ tail; } ;

/* Variables and functions */
 scalar_t__ sig_read_header (struct visorchannel*,int /*<<< orphan*/ ,struct signal_queue_header*) ; 

__attribute__((used)) static bool queue_empty(struct visorchannel *channel, u32 queue)
{
	struct signal_queue_header sig_hdr;

	if (sig_read_header(channel, queue, &sig_hdr))
		return true;
	return (sig_hdr.head == sig_hdr.tail);
}