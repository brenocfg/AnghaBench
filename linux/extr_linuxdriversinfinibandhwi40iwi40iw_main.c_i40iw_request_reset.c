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
struct i40iw_device {int /*<<< orphan*/  client; struct i40e_info* ldev; } ;
struct i40e_info {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* request_reset ) (struct i40e_info*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct i40e_info*,int /*<<< orphan*/ ,int) ; 

void i40iw_request_reset(struct i40iw_device *iwdev)
{
	struct i40e_info *ldev = iwdev->ldev;

	ldev->ops->request_reset(ldev, iwdev->client, 1);
}