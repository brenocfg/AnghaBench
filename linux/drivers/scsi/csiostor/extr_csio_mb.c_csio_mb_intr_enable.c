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
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_PF_HOST_INT_ENABLE_A ; 
 int /*<<< orphan*/  MBMSGRDYINTEN_F ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
csio_mb_intr_enable(struct csio_hw *hw)
{
	csio_wr_reg32(hw, MBMSGRDYINTEN_F, MYPF_REG(CIM_PF_HOST_INT_ENABLE_A));
	csio_rd_reg32(hw, MYPF_REG(CIM_PF_HOST_INT_ENABLE_A));
}