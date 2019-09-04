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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ cookie; } ;
struct ep93xx_dma_desc {TYPE_1__ txd; } ;
struct TYPE_4__ {int /*<<< orphan*/  private; } ;
struct ep93xx_dma_chan {scalar_t__ regs; TYPE_2__ chan; } ;

/* Variables and functions */
 int INTERRUPT_DONE ; 
 int INTERRUPT_NEXT_BUFFER ; 
 int INTERRUPT_UNKNOWN ; 
 scalar_t__ M2M_CONTROL ; 
 scalar_t__ M2M_CONTROL_DONEINT ; 
 scalar_t__ M2M_CONTROL_ENABLE ; 
 scalar_t__ M2M_CONTROL_NFBINT ; 
 scalar_t__ M2M_CONTROL_START ; 
 scalar_t__ M2M_INTERRUPT ; 
 scalar_t__ M2M_INTERRUPT_MASK ; 
 scalar_t__ M2M_STATUS ; 
 scalar_t__ M2M_STATUS_BUF_MASK ; 
 scalar_t__ M2M_STATUS_BUF_NO ; 
 scalar_t__ M2M_STATUS_BUF_ON ; 
 scalar_t__ M2M_STATUS_CTL_MASK ; 
 scalar_t__ M2M_STATUS_CTL_STALL ; 
 scalar_t__ M2M_STATUS_DONE ; 
 scalar_t__ ep93xx_dma_advance_active (struct ep93xx_dma_chan*) ; 
 struct ep93xx_dma_desc* ep93xx_dma_get_active (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  m2m_fill_desc (struct ep93xx_dma_chan*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int m2m_hw_interrupt(struct ep93xx_dma_chan *edmac)
{
	u32 status = readl(edmac->regs + M2M_STATUS);
	u32 ctl_fsm = status & M2M_STATUS_CTL_MASK;
	u32 buf_fsm = status & M2M_STATUS_BUF_MASK;
	bool done = status & M2M_STATUS_DONE;
	bool last_done;
	u32 control;
	struct ep93xx_dma_desc *desc;

	/* Accept only DONE and NFB interrupts */
	if (!(readl(edmac->regs + M2M_INTERRUPT) & M2M_INTERRUPT_MASK))
		return INTERRUPT_UNKNOWN;

	if (done) {
		/* Clear the DONE bit */
		writel(0, edmac->regs + M2M_INTERRUPT);
	}

	/*
	 * Check whether we are done with descriptors or not. This, together
	 * with DMA channel state, determines action to take in interrupt.
	 */
	desc = ep93xx_dma_get_active(edmac);
	last_done = !desc || desc->txd.cookie;

	/*
	 * Use M2M DMA Buffer FSM and Control FSM to check current state of
	 * DMA channel. Using DONE and NFB bits from channel status register
	 * or bits from channel interrupt register is not reliable.
	 */
	if (!last_done &&
	    (buf_fsm == M2M_STATUS_BUF_NO ||
	     buf_fsm == M2M_STATUS_BUF_ON)) {
		/*
		 * Two buffers are ready for update when Buffer FSM is in
		 * DMA_NO_BUF state. Only one buffer can be prepared without
		 * disabling the channel or polling the DONE bit.
		 * To simplify things, always prepare only one buffer.
		 */
		if (ep93xx_dma_advance_active(edmac)) {
			m2m_fill_desc(edmac);
			if (done && !edmac->chan.private) {
				/* Software trigger for memcpy channel */
				control = readl(edmac->regs + M2M_CONTROL);
				control |= M2M_CONTROL_START;
				writel(control, edmac->regs + M2M_CONTROL);
			}
			return INTERRUPT_NEXT_BUFFER;
		} else {
			last_done = true;
		}
	}

	/*
	 * Disable the channel only when Buffer FSM is in DMA_NO_BUF state
	 * and Control FSM is in DMA_STALL state.
	 */
	if (last_done &&
	    buf_fsm == M2M_STATUS_BUF_NO &&
	    ctl_fsm == M2M_STATUS_CTL_STALL) {
		/* Disable interrupts and the channel */
		control = readl(edmac->regs + M2M_CONTROL);
		control &= ~(M2M_CONTROL_DONEINT | M2M_CONTROL_NFBINT
			    | M2M_CONTROL_ENABLE);
		writel(control, edmac->regs + M2M_CONTROL);
		return INTERRUPT_DONE;
	}

	/*
	 * Nothing to do this time.
	 */
	return INTERRUPT_NEXT_BUFFER;
}