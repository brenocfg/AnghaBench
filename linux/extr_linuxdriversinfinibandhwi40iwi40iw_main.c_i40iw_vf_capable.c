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
typedef  scalar_t__ u32 ;
struct i40iw_sc_dev {TYPE_1__** vf_dev; } ;
struct TYPE_4__ {unsigned int max_enabled_vfs; struct i40iw_sc_dev sc_dev; } ;
struct i40iw_handler {TYPE_2__ device; } ;
struct i40e_info {int dummy; } ;
struct i40e_client {int dummy; } ;
struct TYPE_3__ {scalar_t__ vf_id; } ;

/* Variables and functions */
 struct i40iw_handler* i40iw_find_i40e_handler (struct i40e_info*) ; 

__attribute__((used)) static int i40iw_vf_capable(struct i40e_info *ldev,
			    struct i40e_client *client,
			    u32 vf_id)
{
	struct i40iw_handler *hdl;
	struct i40iw_sc_dev *dev;
	unsigned int i;

	hdl = i40iw_find_i40e_handler(ldev);
	if (!hdl)
		return 0;

	dev = &hdl->device.sc_dev;

	for (i = 0; i < hdl->device.max_enabled_vfs; i++) {
		if (!dev->vf_dev[i] || (dev->vf_dev[i]->vf_id == vf_id))
			return 1;
	}

	return 0;
}