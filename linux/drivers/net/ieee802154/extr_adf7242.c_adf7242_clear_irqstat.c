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
struct adf7242_local {int dummy; } ;

/* Variables and functions */
 int IRQ_ADDRESS_VALID ; 
 int IRQ_CCA_COMPLETE ; 
 int IRQ_CSMA_CA ; 
 int IRQ_FRAME_VALID ; 
 int IRQ_RX_PKT_RCVD ; 
 int IRQ_SFD_RX ; 
 int IRQ_SFD_TX ; 
 int IRQ_TX_PKT_SENT ; 
 int /*<<< orphan*/  REG_IRQ1_SRC1 ; 
 int /*<<< orphan*/  adf7242_write_reg (struct adf7242_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adf7242_clear_irqstat(struct adf7242_local *lp)
{
	adf7242_write_reg(lp, REG_IRQ1_SRC1, IRQ_CCA_COMPLETE | IRQ_SFD_RX |
			  IRQ_SFD_TX | IRQ_RX_PKT_RCVD | IRQ_TX_PKT_SENT |
			  IRQ_FRAME_VALID | IRQ_ADDRESS_VALID | IRQ_CSMA_CA);
}