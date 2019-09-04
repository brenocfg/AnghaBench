#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlx5_ib_dev {TYPE_3__* mdev; } ;
struct TYPE_4__ {scalar_t__ mgmt_class; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct TYPE_6__ {TYPE_2__* port_caps; } ;
struct TYPE_5__ {int has_smi; } ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 

__attribute__((used)) static bool can_do_mad_ifc(struct mlx5_ib_dev *dev, u8 port_num,
			   struct ib_mad *in_mad)
{
	if (in_mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_SUBN_LID_ROUTED &&
	    in_mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)
		return true;
	return dev->mdev->port_caps[port_num - 1].has_smi;
}