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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int iwl_read32 (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int,int) ; 

__attribute__((used)) static inline void __iwl_trans_pcie_set_bits_mask(struct iwl_trans *trans,
						  u32 reg, u32 mask, u32 value)
{
	u32 v;

#ifdef CONFIG_IWLWIFI_DEBUG
	WARN_ON_ONCE(value & ~mask);
#endif

	v = iwl_read32(trans, reg);
	v &= ~mask;
	v |= value;
	iwl_write32(trans, reg, v);
}