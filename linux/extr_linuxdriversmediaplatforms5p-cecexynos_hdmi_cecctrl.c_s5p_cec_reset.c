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
typedef  int u8 ;
struct s5p_cec_dev {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ S5P_CEC_RX_CTRL ; 
 int S5P_CEC_RX_CTRL_RESET ; 
 scalar_t__ S5P_CEC_TX_CTRL ; 
 int S5P_CEC_TX_CTRL_RESET ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

void s5p_cec_reset(struct s5p_cec_dev *cec)
{
	u8 reg;

	writeb(S5P_CEC_RX_CTRL_RESET, cec->reg + S5P_CEC_RX_CTRL);
	writeb(S5P_CEC_TX_CTRL_RESET, cec->reg + S5P_CEC_TX_CTRL);

	reg = readb(cec->reg + 0xc4);
	reg &= ~0x1;
	writeb(reg, cec->reg + 0xc4);
}