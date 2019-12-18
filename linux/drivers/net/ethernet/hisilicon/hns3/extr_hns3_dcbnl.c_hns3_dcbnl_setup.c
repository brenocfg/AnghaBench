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
struct net_device {int /*<<< orphan*/ * dcbnl_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  dcb_ops; struct net_device* netdev; } ;
struct hnae3_handle {int flags; TYPE_1__ kinfo; } ;

/* Variables and functions */
 int HNAE3_SUPPORT_VF ; 
 int /*<<< orphan*/  hns3_dcbnl_ops ; 

void hns3_dcbnl_setup(struct hnae3_handle *handle)
{
	struct net_device *dev = handle->kinfo.netdev;

	if ((!handle->kinfo.dcb_ops) || (handle->flags & HNAE3_SUPPORT_VF))
		return;

	dev->dcbnl_ops = &hns3_dcbnl_ops;
}