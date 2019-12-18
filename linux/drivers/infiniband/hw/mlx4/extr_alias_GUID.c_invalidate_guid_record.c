#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct TYPE_7__ {TYPE_2__* ports_guid; } ;
struct TYPE_8__ {TYPE_3__ alias_guid; } ;
struct mlx4_ib_dev {TYPE_4__ sriov; } ;
typedef  int ib_sa_comp_mask ;
struct TYPE_6__ {TYPE_1__* all_rec_per_port; } ;
struct TYPE_5__ {int guid_indexes; int /*<<< orphan*/  status; int /*<<< orphan*/ * all_recs; } ;

/* Variables and functions */
 int GUID_REC_SIZE ; 
 scalar_t__ MLX4_GUID_FOR_DELETE_VAL ; 
 int /*<<< orphan*/  MLX4_GUID_INFO_STATUS_IDLE ; 
 int /*<<< orphan*/  MLX4_GUID_INFO_STATUS_SET ; 
 int NUM_ALIAS_GUID_IN_REC ; 
 int mlx4_ib_get_aguid_comp_mask_from_ix (int) ; 

__attribute__((used)) static void invalidate_guid_record(struct mlx4_ib_dev *dev, u8 port, int index)
{
	int i;
	u64 cur_admin_val;
	ib_sa_comp_mask comp_mask = 0;

	dev->sriov.alias_guid.ports_guid[port - 1].all_rec_per_port[index].status
		= MLX4_GUID_INFO_STATUS_SET;

	/* calculate the comp_mask for that record.*/
	for (i = 0; i < NUM_ALIAS_GUID_IN_REC; i++) {
		cur_admin_val =
			*(u64 *)&dev->sriov.alias_guid.ports_guid[port - 1].
			all_rec_per_port[index].all_recs[GUID_REC_SIZE * i];
		/*
		check the admin value: if it's for delete (~00LL) or
		it is the first guid of the first record (hw guid) or
		the records is not in ownership of the sysadmin and the sm doesn't
		need to assign GUIDs, then don't put it up for assignment.
		*/
		if (MLX4_GUID_FOR_DELETE_VAL == cur_admin_val ||
		    (!index && !i))
			continue;
		comp_mask |= mlx4_ib_get_aguid_comp_mask_from_ix(i);
	}
	dev->sriov.alias_guid.ports_guid[port - 1].
		all_rec_per_port[index].guid_indexes |= comp_mask;
	if (dev->sriov.alias_guid.ports_guid[port - 1].
	    all_rec_per_port[index].guid_indexes)
		dev->sriov.alias_guid.ports_guid[port - 1].
		all_rec_per_port[index].status = MLX4_GUID_INFO_STATUS_IDLE;

}