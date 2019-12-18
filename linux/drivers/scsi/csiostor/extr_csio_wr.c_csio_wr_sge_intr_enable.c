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
typedef  int /*<<< orphan*/  uint16_t ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int CIDXINC_V (int /*<<< orphan*/ ) ; 
 int INGRESSQID_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_GTS_A ; 
 int TIMERREG_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_TIMERREG_RESTART_COUNTER ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_wr_sge_intr_enable(struct csio_hw *hw, uint16_t iqid)
{
	csio_wr_reg32(hw, CIDXINC_V(0)		|
			  INGRESSQID_V(iqid)	|
			  TIMERREG_V(X_TIMERREG_RESTART_COUNTER),
			  MYPF_REG(SGE_PF_GTS_A));
}