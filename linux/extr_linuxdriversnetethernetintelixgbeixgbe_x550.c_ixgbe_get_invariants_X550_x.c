#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * set_phy_power; } ;
struct ixgbe_phy_info {TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct ixgbe_mac_info {TYPE_1__ ops; } ;
struct ixgbe_link_info {int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {struct ixgbe_link_info link; struct ixgbe_phy_info phy; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CS4227 ; 
 int /*<<< orphan*/  ixgbe_get_invariants_X540 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_get_invariants_X550_x(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_phy_info *phy = &hw->phy;
	struct ixgbe_link_info *link = &hw->link;

	/* Start with X540 invariants, since so simular */
	ixgbe_get_invariants_X540(hw);

	if (mac->ops.get_media_type(hw) != ixgbe_media_type_copper)
		phy->ops.set_phy_power = NULL;

	link->addr = IXGBE_CS4227;

	return 0;
}