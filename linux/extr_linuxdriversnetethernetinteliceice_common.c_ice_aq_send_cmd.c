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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int /*<<< orphan*/  adminq; } ;
struct ice_aq_desc {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_sq_send_cmd (struct ice_hw*,int /*<<< orphan*/ *,struct ice_aq_desc*,void*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 

enum ice_status
ice_aq_send_cmd(struct ice_hw *hw, struct ice_aq_desc *desc, void *buf,
		u16 buf_size, struct ice_sq_cd *cd)
{
	return ice_sq_send_cmd(hw, &hw->adminq, desc, buf, buf_size, cd);
}