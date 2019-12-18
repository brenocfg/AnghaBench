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
struct dynpcc_info {scalar_t__ cnt; void* attempt; void* cur; } ;
struct jme_adapter {struct dynpcc_info dpi; } ;

/* Variables and functions */
 int INTR_ENABLE ; 
 int /*<<< orphan*/  JME_IENS ; 
 int /*<<< orphan*/  JME_PCCTX ; 
 int PCCTXQ0_EN ; 
 int PCCTXTO_MASK ; 
 int PCCTXTO_SHIFT ; 
 int PCCTX_MASK ; 
 int PCCTX_SHIFT ; 
 void* PCC_P1 ; 
 int PCC_TX_CNT ; 
 int PCC_TX_TO ; 
 int /*<<< orphan*/  jme_set_rx_pcc (struct jme_adapter*,void*) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
jme_start_irq(struct jme_adapter *jme)
{
	register struct dynpcc_info *dpi = &(jme->dpi);

	jme_set_rx_pcc(jme, PCC_P1);
	dpi->cur		= PCC_P1;
	dpi->attempt		= PCC_P1;
	dpi->cnt		= 0;

	jwrite32(jme, JME_PCCTX,
			((PCC_TX_TO << PCCTXTO_SHIFT) & PCCTXTO_MASK) |
			((PCC_TX_CNT << PCCTX_SHIFT) & PCCTX_MASK) |
			PCCTXQ0_EN
		);

	/*
	 * Enable Interrupts
	 */
	jwrite32(jme, JME_IENS, INTR_ENABLE);
}