#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct d40_gen_dmac {int realtime_en; int realtime_clear; int high_prio_en; int high_prio_clear; } ;
struct TYPE_3__ {int realtime; int high_priority; } ;
struct d40_chan {TYPE_2__* base; TYPE_1__ dma_cfg; } ;
struct TYPE_4__ {int virtbase; struct d40_gen_dmac gen_dmac; } ;

/* Variables and functions */
 int BIT (int) ; 
 int D40_TYPE_TO_EVENT (int) ; 
 int D40_TYPE_TO_GROUP (int) ; 
 scalar_t__ chan_is_logical (struct d40_chan*) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void __d40_set_prio_rt(struct d40_chan *d40c, int dev_type, bool src)
{
	bool realtime = d40c->dma_cfg.realtime;
	bool highprio = d40c->dma_cfg.high_priority;
	u32 rtreg;
	u32 event = D40_TYPE_TO_EVENT(dev_type);
	u32 group = D40_TYPE_TO_GROUP(dev_type);
	u32 bit = BIT(event);
	u32 prioreg;
	struct d40_gen_dmac *dmac = &d40c->base->gen_dmac;

	rtreg = realtime ? dmac->realtime_en : dmac->realtime_clear;
	/*
	 * Due to a hardware bug, in some cases a logical channel triggered by
	 * a high priority destination event line can generate extra packet
	 * transactions.
	 *
	 * The workaround is to not set the high priority level for the
	 * destination event lines that trigger logical channels.
	 */
	if (!src && chan_is_logical(d40c))
		highprio = false;

	prioreg = highprio ? dmac->high_prio_en : dmac->high_prio_clear;

	/* Destination event lines are stored in the upper halfword */
	if (!src)
		bit <<= 16;

	writel(bit, d40c->base->virtbase + prioreg + group * 4);
	writel(bit, d40c->base->virtbase + rtreg + group * 4);
}