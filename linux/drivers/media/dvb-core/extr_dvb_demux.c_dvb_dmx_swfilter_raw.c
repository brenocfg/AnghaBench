#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_demux {int /*<<< orphan*/  lock; TYPE_2__* feed; } ;
struct TYPE_6__ {int /*<<< orphan*/  ts; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ts ) (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  buffer_flags; TYPE_3__ feed; TYPE_1__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dvb_dmx_swfilter_raw(struct dvb_demux *demux, const u8 *buf, size_t count)
{
	unsigned long flags;

	spin_lock_irqsave(&demux->lock, flags);

	demux->feed->cb.ts(buf, count, NULL, 0, &demux->feed->feed.ts,
			   &demux->feed->buffer_flags);

	spin_unlock_irqrestore(&demux->lock, flags);
}