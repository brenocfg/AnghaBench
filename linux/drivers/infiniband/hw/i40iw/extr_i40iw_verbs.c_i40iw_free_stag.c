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
typedef  int u32 ;
struct i40iw_device {int mr_stagmask; int /*<<< orphan*/  allocated_mrs; } ;

/* Variables and functions */
 int I40IW_CQPSQ_STAG_IDX_SHIFT ; 
 int /*<<< orphan*/  i40iw_free_resource (struct i40iw_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40iw_rem_devusecount (struct i40iw_device*) ; 

__attribute__((used)) static void i40iw_free_stag(struct i40iw_device *iwdev, u32 stag)
{
	u32 stag_idx;

	stag_idx = (stag & iwdev->mr_stagmask) >> I40IW_CQPSQ_STAG_IDX_SHIFT;
	i40iw_free_resource(iwdev, iwdev->allocated_mrs, stag_idx);
	i40iw_rem_devusecount(iwdev);
}