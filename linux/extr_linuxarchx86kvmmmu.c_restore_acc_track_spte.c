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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  is_access_track_spte (int) ; 
 int shadow_acc_track_mask ; 
 int shadow_acc_track_saved_bits_mask ; 
 int shadow_acc_track_saved_bits_shift ; 
 int spte_ad_enabled (int) ; 

__attribute__((used)) static u64 restore_acc_track_spte(u64 spte)
{
	u64 new_spte = spte;
	u64 saved_bits = (spte >> shadow_acc_track_saved_bits_shift)
			 & shadow_acc_track_saved_bits_mask;

	WARN_ON_ONCE(spte_ad_enabled(spte));
	WARN_ON_ONCE(!is_access_track_spte(spte));

	new_spte &= ~shadow_acc_track_mask;
	new_spte &= ~(shadow_acc_track_saved_bits_mask <<
		      shadow_acc_track_saved_bits_shift);
	new_spte |= saved_bits;

	return new_spte;
}