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

/* Variables and functions */
 int DSI_IRQ_ACK_TRIGGER ; 
 int DSI_IRQ_CHANNEL_MASK ; 
 int DSI_IRQ_COMPLEXIO_ERR ; 
 int DSI_IRQ_HS_TX_TIMEOUT ; 
 int DSI_IRQ_LDO_POWER_GOOD ; 
 int DSI_IRQ_LP_RX_TIMEOUT ; 
 int DSI_IRQ_PLL_LOCK ; 
 int DSI_IRQ_PLL_RECALL ; 
 int DSI_IRQ_PLL_UNLOCK ; 
 int DSI_IRQ_RESYNC ; 
 int DSI_IRQ_SYNC_LOST ; 
 int DSI_IRQ_TA_TIMEOUT ; 
 int DSI_IRQ_TE_TRIGGER ; 
 int DSI_IRQ_VC0 ; 
 int DSI_IRQ_VC1 ; 
 int DSI_IRQ_VC2 ; 
 int DSI_IRQ_VC3 ; 
 int DSI_IRQ_WAKEUP ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ verbose_irq ; 

__attribute__((used)) static void print_irq_status(u32 status)
{
	if (status == 0)
		return;

	if (!verbose_irq && (status & ~DSI_IRQ_CHANNEL_MASK) == 0)
		return;

#define PIS(x) (status & DSI_IRQ_##x) ? (#x " ") : ""

	pr_debug("DSI IRQ: 0x%x: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		status,
		verbose_irq ? PIS(VC0) : "",
		verbose_irq ? PIS(VC1) : "",
		verbose_irq ? PIS(VC2) : "",
		verbose_irq ? PIS(VC3) : "",
		PIS(WAKEUP),
		PIS(RESYNC),
		PIS(PLL_LOCK),
		PIS(PLL_UNLOCK),
		PIS(PLL_RECALL),
		PIS(COMPLEXIO_ERR),
		PIS(HS_TX_TIMEOUT),
		PIS(LP_RX_TIMEOUT),
		PIS(TE_TRIGGER),
		PIS(ACK_TRIGGER),
		PIS(SYNC_LOST),
		PIS(LDO_POWER_GOOD),
		PIS(TA_TIMEOUT));
#undef PIS
}