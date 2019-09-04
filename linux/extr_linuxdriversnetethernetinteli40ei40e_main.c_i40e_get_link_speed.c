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
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_4__ {int link_speed; } ;
struct TYPE_5__ {TYPE_1__ link_info; } ;
struct TYPE_6__ {TYPE_2__ phy; } ;
struct i40e_pf {TYPE_3__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
#define  I40E_LINK_SPEED_10GB 132 
#define  I40E_LINK_SPEED_1GB 131 
#define  I40E_LINK_SPEED_20GB 130 
#define  I40E_LINK_SPEED_25GB 129 
#define  I40E_LINK_SPEED_40GB 128 

__attribute__((used)) static int i40e_get_link_speed(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;

	switch (pf->hw.phy.link_info.link_speed) {
	case I40E_LINK_SPEED_40GB:
		return 40000;
	case I40E_LINK_SPEED_25GB:
		return 25000;
	case I40E_LINK_SPEED_20GB:
		return 20000;
	case I40E_LINK_SPEED_10GB:
		return 10000;
	case I40E_LINK_SPEED_1GB:
		return 1000;
	default:
		return -EINVAL;
	}
}