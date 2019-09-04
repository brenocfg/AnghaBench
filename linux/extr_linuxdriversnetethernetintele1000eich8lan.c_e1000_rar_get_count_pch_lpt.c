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
typedef  int u32 ;
struct TYPE_2__ {int rar_entry_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int E1000_FWSM_WLOCK_MAC_MASK ; 
 int E1000_FWSM_WLOCK_MAC_SHIFT ; 
 int /*<<< orphan*/  FWSM ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 e1000_rar_get_count_pch_lpt(struct e1000_hw *hw)
{
	u32 wlock_mac;
	u32 num_entries;

	wlock_mac = er32(FWSM) & E1000_FWSM_WLOCK_MAC_MASK;
	wlock_mac >>= E1000_FWSM_WLOCK_MAC_SHIFT;

	switch (wlock_mac) {
	case 0:
		/* All SHRA[0..10] and RAR[0] available */
		num_entries = hw->mac.rar_entry_count;
		break;
	case 1:
		/* Only RAR[0] available */
		num_entries = 1;
		break;
	default:
		/* SHRA[0..(wlock_mac - 1)] available + RAR[0] */
		num_entries = wlock_mac + 1;
		break;
	}

	return num_entries;
}