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
struct ice_vsi {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_VSI_FLAG_MMAC_FLTR_CHANGED ; 
 int /*<<< orphan*/  ICE_VSI_FLAG_UMAC_FLTR_CHANGED ; 
 int /*<<< orphan*/  ICE_VSI_FLAG_VLAN_FLTR_CHANGED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_vsi_fltr_changed(struct ice_vsi *vsi)
{
	return test_bit(ICE_VSI_FLAG_UMAC_FLTR_CHANGED, vsi->flags) ||
	       test_bit(ICE_VSI_FLAG_MMAC_FLTR_CHANGED, vsi->flags) ||
	       test_bit(ICE_VSI_FLAG_VLAN_FLTR_CHANGED, vsi->flags);
}