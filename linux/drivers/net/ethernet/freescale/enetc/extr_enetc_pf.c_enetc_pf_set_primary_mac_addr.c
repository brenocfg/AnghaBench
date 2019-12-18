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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct enetc_hw {scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ ENETC_PSIPMAR0 (int) ; 
 scalar_t__ ENETC_PSIPMAR1 (int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void enetc_pf_set_primary_mac_addr(struct enetc_hw *hw, int si,
					  const u8 *addr)
{
	u32 upper = *(const u32 *)addr;
	u16 lower = *(const u16 *)(addr + 4);

	__raw_writel(upper, hw->port + ENETC_PSIPMAR0(si));
	__raw_writew(lower, hw->port + ENETC_PSIPMAR1(si));
}