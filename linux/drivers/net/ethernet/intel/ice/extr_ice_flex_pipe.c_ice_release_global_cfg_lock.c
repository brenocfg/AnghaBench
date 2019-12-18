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
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_GLOBAL_CFG_LOCK_RES_ID ; 
 int /*<<< orphan*/  ice_global_cfg_lock_sw ; 
 int /*<<< orphan*/  ice_release_res (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_release_global_cfg_lock(struct ice_hw *hw)
{
	mutex_unlock(&ice_global_cfg_lock_sw);
	ice_release_res(hw, ICE_GLOBAL_CFG_LOCK_RES_ID);
}