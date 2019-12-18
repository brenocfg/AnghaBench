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
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_PSIIER ; 
 int ENETC_PSIIER_MR_MASK ; 
 int enetc_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_wr (struct enetc_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enetc_msg_enable_mr_int(struct enetc_hw *hw)
{
	u32 psiier = enetc_rd(hw, ENETC_PSIIER);

	enetc_wr(hw, ENETC_PSIIER, psiier | ENETC_PSIIER_MR_MASK);
}