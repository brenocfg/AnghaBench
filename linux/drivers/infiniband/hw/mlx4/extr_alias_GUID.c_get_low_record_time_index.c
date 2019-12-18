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
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
struct mlx4_sriov_alias_guid_info_rec_det {scalar_t__ status; scalar_t__ time_to_run; scalar_t__ guid_indexes; } ;
struct TYPE_5__ {TYPE_1__* ports_guid; } ;
struct TYPE_6__ {TYPE_2__ alias_guid; } ;
struct mlx4_ib_dev {TYPE_3__ sriov; } ;
struct TYPE_4__ {struct mlx4_sriov_alias_guid_info_rec_det* all_rec_per_port; } ;

/* Variables and functions */
 scalar_t__ MLX4_GUID_INFO_STATUS_IDLE ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int NUM_ALIAS_GUID_REC_IN_PORT ; 
 int div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_boottime_ns () ; 

__attribute__((used)) static int get_low_record_time_index(struct mlx4_ib_dev *dev, u8 port,
				     int *resched_delay_sec)
{
	int record_index = -1;
	u64 low_record_time = 0;
	struct mlx4_sriov_alias_guid_info_rec_det rec;
	int j;

	for (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) {
		rec = dev->sriov.alias_guid.ports_guid[port].
			all_rec_per_port[j];
		if (rec.status == MLX4_GUID_INFO_STATUS_IDLE &&
		    rec.guid_indexes) {
			if (record_index == -1 ||
			    rec.time_to_run < low_record_time) {
				record_index = j;
				low_record_time = rec.time_to_run;
			}
		}
	}
	if (resched_delay_sec) {
		u64 curr_time = ktime_get_boottime_ns();

		*resched_delay_sec = (low_record_time < curr_time) ? 0 :
			div_u64((low_record_time - curr_time), NSEC_PER_SEC);
	}

	return record_index;
}