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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ PKEY_LOW_15_MASK ; 
 scalar_t__ PKEY_MEMBER_MASK ; 

__attribute__((used)) static inline int egress_pkey_matches_entry(u16 pkey, u16 ent)
{
	u16 mkey = pkey & PKEY_LOW_15_MASK;
	u16 mentry = ent & PKEY_LOW_15_MASK;

	if (mkey == mentry) {
		/*
		 * If pkey[15] is set (full partition member),
		 * is bit 15 in the corresponding table element
		 * clear (limited member)?
		 */
		if (pkey & PKEY_MEMBER_MASK)
			return !!(ent & PKEY_MEMBER_MASK);
		return 1;
	}
	return 0;
}