#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ngene_channel {struct ngene* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
struct ngene {TYPE_1__ tsout_rbuf; } ;

/* Variables and functions */
 int DF_SWAP32 ; 
 int /*<<< orphan*/  FillTSBuffer (void*,int,int) ; 
 int dvb_ringbuffer_avail (TYPE_1__*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_read (TYPE_1__*,void*,int) ; 
 int /*<<< orphan*/  swap_buffer (int*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void *tsout_exchange(void *priv, void *buf, u32 len, u32 clock, u32 flags)
{
	struct ngene_channel *chan = priv;
	struct ngene *dev = chan->dev;
	u32 alen;

	alen = dvb_ringbuffer_avail(&dev->tsout_rbuf);
	alen -= alen % 188;

	if (alen < len)
		FillTSBuffer(buf + alen, len - alen, flags);
	else
		alen = len;
	dvb_ringbuffer_read(&dev->tsout_rbuf, buf, alen);
	if (flags & DF_SWAP32)
		swap_buffer((u32 *)buf, alen);
	wake_up_interruptible(&dev->tsout_rbuf.queue);
	return buf;
}