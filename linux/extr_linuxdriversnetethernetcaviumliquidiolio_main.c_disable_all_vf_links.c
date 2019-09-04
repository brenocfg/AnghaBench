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
struct TYPE_3__ {int max_vfs; } ;
struct octeon_device {int ifcount; TYPE_2__* props; TYPE_1__ sriov_info; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_VF_LINK_STATE_DISABLE ; 
 int /*<<< orphan*/  liquidio_set_vf_link_state (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_all_vf_links(struct octeon_device *oct)
{
	struct net_device *netdev;
	int max_vfs, vf, i;

	if (!oct)
		return;

	max_vfs = oct->sriov_info.max_vfs;

	for (i = 0; i < oct->ifcount; i++) {
		netdev = oct->props[i].netdev;
		if (!netdev)
			continue;

		for (vf = 0; vf < max_vfs; vf++)
			liquidio_set_vf_link_state(netdev, vf,
						   IFLA_VF_LINK_STATE_DISABLE);
	}
}