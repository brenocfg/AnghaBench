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
typedef  int /*<<< orphan*/  u8 ;
struct s5p_cec_dev {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ S5P_CEC_IRQ_MASK ; 
 int /*<<< orphan*/  S5P_CEC_IRQ_TX_DONE ; 
 int /*<<< orphan*/  S5P_CEC_IRQ_TX_ERROR ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

void s5p_cec_mask_tx_interrupts(struct s5p_cec_dev *cec)
{
	u8 reg;

	reg = readb(cec->reg + S5P_CEC_IRQ_MASK);
	reg |= S5P_CEC_IRQ_TX_DONE;
	reg |= S5P_CEC_IRQ_TX_ERROR;
	writeb(reg, cec->reg + S5P_CEC_IRQ_MASK);
}