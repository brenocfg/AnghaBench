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
 int /*<<< orphan*/  ENETC_PSIVHFR0 (int) ; 
 int /*<<< orphan*/  ENETC_PSIVHFR1 (int) ; 
 int /*<<< orphan*/  enetc_port_wr (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_set_vlan_ht_filter(struct enetc_hw *hw, int si_idx,
				     u32 *hash)
{
	enetc_port_wr(hw, ENETC_PSIVHFR0(si_idx), *hash);
	enetc_port_wr(hw, ENETC_PSIVHFR1(si_idx), *(hash + 1));
}