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
struct visorchannel {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  physaddr; scalar_t__ requested; scalar_t__ mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct visorchannel*) ; 
 int /*<<< orphan*/  memunmap (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void visorchannel_destroy(struct visorchannel *channel)
{
	if (!channel)
		return;

	if (channel->mapped) {
		memunmap(channel->mapped);
		if (channel->requested)
			release_mem_region(channel->physaddr, channel->nbytes);
	}
	kfree(channel);
}