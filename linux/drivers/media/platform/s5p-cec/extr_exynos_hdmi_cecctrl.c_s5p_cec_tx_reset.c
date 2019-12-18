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
 scalar_t__ S5P_CEC_TX_CTRL ; 
 int /*<<< orphan*/  S5P_CEC_TX_CTRL_RESET ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

void s5p_cec_tx_reset(struct s5p_cec_dev *cec)
{
	writeb(S5P_CEC_TX_CTRL_RESET, cec->reg + S5P_CEC_TX_CTRL);
}