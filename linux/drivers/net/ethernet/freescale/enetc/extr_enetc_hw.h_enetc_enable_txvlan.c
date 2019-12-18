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
 int /*<<< orphan*/  ENETC_TBMR ; 
 int ENETC_TBMR_VIH ; 
 int enetc_txbdr_rd (struct enetc_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_txbdr_wr (struct enetc_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void enetc_enable_txvlan(struct enetc_hw *hw, int si_idx,
				       bool en)
{
	u32 val = enetc_txbdr_rd(hw, si_idx, ENETC_TBMR);

	val = (val & ~ENETC_TBMR_VIH) | (en ? ENETC_TBMR_VIH : 0);
	enetc_txbdr_wr(hw, si_idx, ENETC_TBMR, val);
}