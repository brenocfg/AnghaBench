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
typedef  scalar_t__ ulong ;
struct visorchannel {scalar_t__ nbytes; scalar_t__ mapped; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 

int visorchannel_read(struct visorchannel *channel, ulong offset, void *dest,
		      ulong nbytes)
{
	if (offset + nbytes > channel->nbytes)
		return -EIO;

	memcpy(dest, channel->mapped + offset, nbytes);
	return 0;
}