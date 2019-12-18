#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ max_enabled_vfs; } ;
struct i40iw_handler {TYPE_1__ device; } ;
struct i40e_info {int dummy; } ;
struct i40e_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ I40IW_MAX_PE_ENABLED_VF_COUNT ; 
 struct i40iw_handler* i40iw_find_i40e_handler (struct i40e_info*) ; 

__attribute__((used)) static void i40iw_vf_enable(struct i40e_info *ldev,
			    struct i40e_client *client,
			    u32 num_vfs)
{
	struct i40iw_handler *hdl;

	hdl = i40iw_find_i40e_handler(ldev);
	if (!hdl)
		return;

	if (num_vfs > I40IW_MAX_PE_ENABLED_VF_COUNT)
		hdl->device.max_enabled_vfs = I40IW_MAX_PE_ENABLED_VF_COUNT;
	else
		hdl->device.max_enabled_vfs = num_vfs;
}