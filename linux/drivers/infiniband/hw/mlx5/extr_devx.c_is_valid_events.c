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
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;
struct devx_obj {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int MAX_SUPP_EVENT_NUM ; 
 int /*<<< orphan*/ * MLX5_CAP_DEV_EVENT (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 unsigned long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_cap ; 
 int is_valid_events_legacy (int,int*,struct devx_obj*) ; 
 int /*<<< orphan*/  user_affiliated_events ; 
 int /*<<< orphan*/  user_unaffiliated_events ; 

__attribute__((used)) static bool is_valid_events(struct mlx5_core_dev *dev,
			    int num_events, u16 *event_type_num_list,
			    struct devx_obj *obj)
{
	__be64 *aff_events;
	__be64 *unaff_events;
	int mask_entry;
	int mask_bit;
	int i;

	if (MLX5_CAP_GEN(dev, event_cap)) {
		aff_events = MLX5_CAP_DEV_EVENT(dev,
						user_affiliated_events);
		unaff_events = MLX5_CAP_DEV_EVENT(dev,
						  user_unaffiliated_events);
	} else {
		return is_valid_events_legacy(num_events, event_type_num_list,
					      obj);
	}

	for (i = 0; i < num_events; i++) {
		if (event_type_num_list[i] > MAX_SUPP_EVENT_NUM)
			return false;

		mask_entry = event_type_num_list[i] / 64;
		mask_bit = event_type_num_list[i] % 64;

		if (obj) {
			/* CQ completion */
			if (event_type_num_list[i] == 0)
				continue;

			if (!(be64_to_cpu(aff_events[mask_entry]) &
					(1ull << mask_bit)))
				return false;

			continue;
		}

		if (!(be64_to_cpu(unaff_events[mask_entry]) &
				(1ull << mask_bit)))
			return false;
	}

	return true;
}