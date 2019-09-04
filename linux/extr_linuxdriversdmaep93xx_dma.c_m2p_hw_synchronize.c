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
typedef  int u32 ;
struct ep93xx_dma_chan {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ M2P_CONTROL ; 
 int M2P_CONTROL_NFBINT ; 
 int M2P_CONTROL_STALLINT ; 
 scalar_t__ M2P_STATE_ON ; 
 scalar_t__ m2p_channel_state (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  m2p_set_control (struct ep93xx_dma_chan*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void m2p_hw_synchronize(struct ep93xx_dma_chan *edmac)
{
	unsigned long flags;
	u32 control;

	spin_lock_irqsave(&edmac->lock, flags);
	control = readl(edmac->regs + M2P_CONTROL);
	control &= ~(M2P_CONTROL_STALLINT | M2P_CONTROL_NFBINT);
	m2p_set_control(edmac, control);
	spin_unlock_irqrestore(&edmac->lock, flags);

	while (m2p_channel_state(edmac) >= M2P_STATE_ON)
		schedule();
}