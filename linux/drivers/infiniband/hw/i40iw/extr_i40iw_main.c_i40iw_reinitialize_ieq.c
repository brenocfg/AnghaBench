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
struct i40iw_sc_dev {scalar_t__ back_dev; } ;
struct i40iw_device {int reset; int /*<<< orphan*/  vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_PUDA_RSRC_TYPE_IEQ ; 
 scalar_t__ i40iw_initialize_ieq (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_puda_dele_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40iw_request_reset (struct i40iw_device*) ; 

void i40iw_reinitialize_ieq(struct i40iw_sc_dev *dev)
{
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;

	i40iw_puda_dele_resources(&iwdev->vsi, I40IW_PUDA_RSRC_TYPE_IEQ, false);
	if (i40iw_initialize_ieq(iwdev)) {
		iwdev->reset = true;
		i40iw_request_reset(iwdev);
	}
}