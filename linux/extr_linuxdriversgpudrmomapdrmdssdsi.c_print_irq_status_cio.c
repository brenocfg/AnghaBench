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
 int DSI_CIO_IRQ_ERRCONTENTIONLP0_1 ; 
 int DSI_CIO_IRQ_ERRCONTENTIONLP0_2 ; 
 int DSI_CIO_IRQ_ERRCONTENTIONLP0_3 ; 
 int DSI_CIO_IRQ_ERRCONTENTIONLP1_1 ; 
 int DSI_CIO_IRQ_ERRCONTENTIONLP1_2 ; 
 int DSI_CIO_IRQ_ERRCONTENTIONLP1_3 ; 
 int DSI_CIO_IRQ_ERRCONTROL1 ; 
 int DSI_CIO_IRQ_ERRCONTROL2 ; 
 int DSI_CIO_IRQ_ERRCONTROL3 ; 
 int DSI_CIO_IRQ_ERRESC1 ; 
 int DSI_CIO_IRQ_ERRESC2 ; 
 int DSI_CIO_IRQ_ERRESC3 ; 
 int DSI_CIO_IRQ_ERRSYNCESC1 ; 
 int DSI_CIO_IRQ_ERRSYNCESC2 ; 
 int DSI_CIO_IRQ_ERRSYNCESC3 ; 
 int DSI_CIO_IRQ_STATEULPS1 ; 
 int DSI_CIO_IRQ_STATEULPS2 ; 
 int DSI_CIO_IRQ_STATEULPS3 ; 
 int DSI_CIO_IRQ_ULPSACTIVENOT_ALL0 ; 
 int DSI_CIO_IRQ_ULPSACTIVENOT_ALL1 ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void print_irq_status_cio(u32 status)
{
	if (status == 0)
		return;

#define PIS(x) (status & DSI_CIO_IRQ_##x) ? (#x " ") : ""

	pr_debug("DSI CIO IRQ 0x%x: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		status,
		PIS(ERRSYNCESC1),
		PIS(ERRSYNCESC2),
		PIS(ERRSYNCESC3),
		PIS(ERRESC1),
		PIS(ERRESC2),
		PIS(ERRESC3),
		PIS(ERRCONTROL1),
		PIS(ERRCONTROL2),
		PIS(ERRCONTROL3),
		PIS(STATEULPS1),
		PIS(STATEULPS2),
		PIS(STATEULPS3),
		PIS(ERRCONTENTIONLP0_1),
		PIS(ERRCONTENTIONLP1_1),
		PIS(ERRCONTENTIONLP0_2),
		PIS(ERRCONTENTIONLP1_2),
		PIS(ERRCONTENTIONLP0_3),
		PIS(ERRCONTENTIONLP1_3),
		PIS(ULPSACTIVENOT_ALL0),
		PIS(ULPSACTIVENOT_ALL1));
#undef PIS
}