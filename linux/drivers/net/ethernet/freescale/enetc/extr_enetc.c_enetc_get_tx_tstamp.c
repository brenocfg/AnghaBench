#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tstamp; } ;
union enetc_tx_bd {TYPE_1__ wb; } ;
typedef  int u64 ;
typedef  int u32 ;
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_SICTR0 ; 
 int /*<<< orphan*/  ENETC_SICTR1 ; 
 int enetc_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_get_tx_tstamp(struct enetc_hw *hw, union enetc_tx_bd *txbd,
				u64 *tstamp)
{
	u32 lo, hi, tstamp_lo;

	lo = enetc_rd(hw, ENETC_SICTR0);
	hi = enetc_rd(hw, ENETC_SICTR1);
	tstamp_lo = le32_to_cpu(txbd->wb.tstamp);
	if (lo <= tstamp_lo)
		hi -= 1;
	*tstamp = (u64)hi << 32 | tstamp_lo;
}