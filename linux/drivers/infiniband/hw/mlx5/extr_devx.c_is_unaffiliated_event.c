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
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned long MAX_SUPP_EVENT_NUM ; 
 int /*<<< orphan*/ * MLX5_CAP_DEV_EVENT (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_cap ; 
 int is_legacy_unaffiliated_event_num (unsigned long) ; 
 int /*<<< orphan*/  user_unaffiliated_events ; 

__attribute__((used)) static bool is_unaffiliated_event(struct mlx5_core_dev *dev,
				  unsigned long event_type)
{
	__be64 *unaff_events;
	int mask_entry;
	int mask_bit;

	if (!MLX5_CAP_GEN(dev, event_cap))
		return is_legacy_unaffiliated_event_num(event_type);

	unaff_events = MLX5_CAP_DEV_EVENT(dev,
					  user_unaffiliated_events);
	WARN_ON(event_type > MAX_SUPP_EVENT_NUM);

	mask_entry = event_type / 64;
	mask_bit = event_type % 64;

	if (!(be64_to_cpu(unaff_events[mask_entry]) & (1ull << mask_bit)))
		return false;

	return true;
}