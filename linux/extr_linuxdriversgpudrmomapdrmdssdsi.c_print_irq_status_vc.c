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
 int DSI_VC_IRQ_BTA ; 
 int DSI_VC_IRQ_CS ; 
 int DSI_VC_IRQ_ECC_CORR ; 
 int DSI_VC_IRQ_ECC_NO_CORR ; 
 int DSI_VC_IRQ_FIFO_RX_OVF ; 
 int DSI_VC_IRQ_FIFO_TX_OVF ; 
 int DSI_VC_IRQ_FIFO_TX_UDF ; 
 int DSI_VC_IRQ_PACKET_SENT ; 
 int DSI_VC_IRQ_PP_BUSY_CHANGE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ verbose_irq ; 

__attribute__((used)) static void print_irq_status_vc(int channel, u32 status)
{
	if (status == 0)
		return;

	if (!verbose_irq && (status & ~DSI_VC_IRQ_PACKET_SENT) == 0)
		return;

#define PIS(x) (status & DSI_VC_IRQ_##x) ? (#x " ") : ""

	pr_debug("DSI VC(%d) IRQ 0x%x: %s%s%s%s%s%s%s%s%s\n",
		channel,
		status,
		PIS(CS),
		PIS(ECC_CORR),
		PIS(ECC_NO_CORR),
		verbose_irq ? PIS(PACKET_SENT) : "",
		PIS(BTA),
		PIS(FIFO_TX_OVF),
		PIS(FIFO_RX_OVF),
		PIS(FIFO_TX_UDF),
		PIS(PP_BUSY_CHANGE));
#undef PIS
}