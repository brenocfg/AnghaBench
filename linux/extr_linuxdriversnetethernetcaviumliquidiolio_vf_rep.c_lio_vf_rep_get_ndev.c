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
struct TYPE_2__ {struct net_device** ndev; } ;
struct octeon_device {int pf_num; TYPE_1__ vf_rep_list; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CN23XX_MAX_VFS_PER_PF ; 

__attribute__((used)) static struct net_device *
lio_vf_rep_get_ndev(struct octeon_device *oct, int ifidx)
{
	int vf_id, max_vfs = CN23XX_MAX_VFS_PER_PF + 1;
	int vfid_mask = max_vfs - 1;

	if (ifidx <= oct->pf_num * max_vfs ||
	    ifidx >= oct->pf_num * max_vfs + max_vfs)
		return NULL;

	/* ifidx 1-63 for PF0 VFs
	 * ifidx 65-127 for PF1 VFs
	 */
	vf_id = (ifidx & vfid_mask) - 1;

	return oct->vf_rep_list.ndev[vf_id];
}