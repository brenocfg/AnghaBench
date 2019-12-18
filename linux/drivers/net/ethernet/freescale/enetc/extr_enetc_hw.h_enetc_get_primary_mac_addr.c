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
struct enetc_hw {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ ENETC_SIPMAR0 ; 
 scalar_t__ ENETC_SIPMAR1 ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_readw (scalar_t__) ; 

__attribute__((used)) static inline void enetc_get_primary_mac_addr(struct enetc_hw *hw, u8 *addr)
{
	*(u32 *)addr = __raw_readl(hw->reg + ENETC_SIPMAR0);
	*(u16 *)(addr + 4) = __raw_readw(hw->reg + ENETC_SIPMAR1);
}