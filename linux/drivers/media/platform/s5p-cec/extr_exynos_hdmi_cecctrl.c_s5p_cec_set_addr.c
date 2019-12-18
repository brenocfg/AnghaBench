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
struct s5p_cec_dev {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ S5P_CEC_LOGIC_ADDR ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

void s5p_cec_set_addr(struct s5p_cec_dev *cec, u32 addr)
{
	writeb(addr & 0x0F, cec->reg + S5P_CEC_LOGIC_ADDR);
}