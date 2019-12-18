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
struct s5p_cec_dev {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ S5P_CEC_IRQ_CLEAR ; 
 int S5P_CEC_IRQ_RX_DONE ; 
 int S5P_CEC_IRQ_RX_ERROR ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

void s5p_clr_pending_rx(struct s5p_cec_dev *cec)
{
	writeb(S5P_CEC_IRQ_RX_DONE | S5P_CEC_IRQ_RX_ERROR,
	       cec->reg + S5P_CEC_IRQ_CLEAR);
}