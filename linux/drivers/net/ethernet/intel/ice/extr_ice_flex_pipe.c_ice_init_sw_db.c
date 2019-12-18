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
struct ice_hw {int dummy; } ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;

/* Variables and functions */
 scalar_t__ ICE_BLK_COUNT ; 
 int /*<<< orphan*/  ice_init_sw_xlt1_db (struct ice_hw*,int) ; 
 int /*<<< orphan*/  ice_init_sw_xlt2_db (struct ice_hw*,int) ; 

__attribute__((used)) static void ice_init_sw_db(struct ice_hw *hw)
{
	u16 i;

	for (i = 0; i < ICE_BLK_COUNT; i++) {
		ice_init_sw_xlt1_db(hw, (enum ice_block)i);
		ice_init_sw_xlt2_db(hw, (enum ice_block)i);
	}
}