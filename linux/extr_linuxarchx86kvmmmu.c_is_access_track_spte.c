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
 int shadow_acc_track_mask ; 
 int /*<<< orphan*/  spte_ad_enabled (int) ; 

__attribute__((used)) static inline bool is_access_track_spte(u64 spte)
{
	return !spte_ad_enabled(spte) && (spte & shadow_acc_track_mask) == 0;
}