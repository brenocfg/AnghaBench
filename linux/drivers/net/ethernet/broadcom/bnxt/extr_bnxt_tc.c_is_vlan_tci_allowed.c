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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ is_vid_exactmatch (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_pcp_exactmatch (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_pcp_wildcarded (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_pcp_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_vlan_tci_allowed(__be16  vlan_tci_mask,
				__be16  vlan_tci)
{
	/* VLAN priority must be either exactly zero or fully wildcarded and
	 * VLAN id must be exact match.
	 */
	if (is_vid_exactmatch(vlan_tci_mask) &&
	    ((is_vlan_pcp_exactmatch(vlan_tci_mask) &&
	      is_vlan_pcp_zero(vlan_tci)) ||
	     is_vlan_pcp_wildcarded(vlan_tci_mask)))
		return true;

	return false;
}