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
struct TYPE_3__ {scalar_t__ mode; int flags; } ;
struct slgt_info {int tx_enabled; size_t tbuf_start; int drop_rts_on_tx_done; int signals; int tx_active; TYPE_2__* tbufs; TYPE_1__ params; } ;
struct TYPE_4__ {scalar_t__ pdesc; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 int BIT1 ; 
 int BIT2 ; 
 int HDLC_FLAG_AUTO_RTS ; 
 int /*<<< orphan*/  IRQ_TXDATA ; 
 unsigned short IRQ_TXIDLE ; 
 unsigned short IRQ_TXUNDER ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int /*<<< orphan*/  SSR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TDCSR ; 
 int /*<<< orphan*/  TDDAR ; 
 scalar_t__ desc_count (TYPE_2__) ; 
 int /*<<< orphan*/  get_signals (struct slgt_info*) ; 
 int rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_signals (struct slgt_info*) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slgt_irq_on (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tx_start(struct slgt_info *info)
{
	if (!info->tx_enabled) {
		wr_reg16(info, TCR,
			 (unsigned short)((rd_reg16(info, TCR) | BIT1) & ~BIT2));
		info->tx_enabled = true;
	}

	if (desc_count(info->tbufs[info->tbuf_start])) {
		info->drop_rts_on_tx_done = false;

		if (info->params.mode != MGSL_MODE_ASYNC) {
			if (info->params.flags & HDLC_FLAG_AUTO_RTS) {
				get_signals(info);
				if (!(info->signals & SerialSignal_RTS)) {
					info->signals |= SerialSignal_RTS;
					set_signals(info);
					info->drop_rts_on_tx_done = true;
				}
			}

			slgt_irq_off(info, IRQ_TXDATA);
			slgt_irq_on(info, IRQ_TXUNDER + IRQ_TXIDLE);
			/* clear tx idle and underrun status bits */
			wr_reg16(info, SSR, (unsigned short)(IRQ_TXIDLE + IRQ_TXUNDER));
		} else {
			slgt_irq_off(info, IRQ_TXDATA);
			slgt_irq_on(info, IRQ_TXIDLE);
			/* clear tx idle status bit */
			wr_reg16(info, SSR, IRQ_TXIDLE);
		}
		/* set 1st descriptor address and start DMA */
		wr_reg32(info, TDDAR, info->tbufs[info->tbuf_start].pdesc);
		wr_reg32(info, TDCSR, BIT2 + BIT0);
		info->tx_active = true;
	}
}