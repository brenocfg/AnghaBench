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
 int /*<<< orphan*/  is_access_track_spte (int) ; 
 int spte_shadow_accessed_mask (int) ; 

__attribute__((used)) static bool is_accessed_spte(u64 spte)
{
	u64 accessed_mask = spte_shadow_accessed_mask(spte);

	return accessed_mask ? spte & accessed_mask
			     : !is_access_track_spte(spte);
}