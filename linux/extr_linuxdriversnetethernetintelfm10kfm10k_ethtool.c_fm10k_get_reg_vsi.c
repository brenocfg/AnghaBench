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
typedef  int /*<<< orphan*/  u32 ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FM10K_MRQC (int) ; 
 int FM10K_REGS_LEN_VSI ; 
 int /*<<< orphan*/  FM10K_RETA (int,int) ; 
 int /*<<< orphan*/  FM10K_RSSRK (int,int) ; 
 int /*<<< orphan*/  fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_get_reg_vsi(struct fm10k_hw *hw, u32 *buff, int i)
{
	int idx = 0, j;

	buff[idx++] = fm10k_read_reg(hw, FM10K_MRQC(i));
	for (j = 0; j < 10; j++)
		buff[idx++] = fm10k_read_reg(hw, FM10K_RSSRK(i, j));
	for (j = 0; j < 32; j++)
		buff[idx++] = fm10k_read_reg(hw, FM10K_RETA(i, j));

	BUG_ON(idx != FM10K_REGS_LEN_VSI);
}