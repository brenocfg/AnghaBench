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
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_TBMR ; 
 int /*<<< orphan*/  ENETC_TBMR_PRIO_MASK ; 
 int /*<<< orphan*/  ENETC_TBMR_SET_PRIO (int) ; 
 int /*<<< orphan*/  enetc_txbdr_rd (struct enetc_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_txbdr_wr (struct enetc_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void enetc_set_bdr_prio(struct enetc_hw *hw, int bdr_idx,
				      int prio)
{
	u32 val = enetc_txbdr_rd(hw, bdr_idx, ENETC_TBMR);

	val &= ~ENETC_TBMR_PRIO_MASK;
	val |= ENETC_TBMR_SET_PRIO(prio);
	enetc_txbdr_wr(hw, bdr_idx, ENETC_TBMR, val);
}