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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mlx5_monitor_counter_ppcnt { ____Placeholder_mlx5_monitor_counter_ppcnt } mlx5_monitor_counter_ppcnt ;
struct TYPE_2__ {int /*<<< orphan*/  counter; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int MLX5_QUERY_MONITOR_CNT_TYPE_PPCNT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int NUM_REQ_PPCNT_COUNTER_S1 ; 
 TYPE_1__* monitor_counter ; 
 int /*<<< orphan*/  set_monitor_counter_in ; 

__attribute__((used)) static int fill_monitor_counter_ppcnt_set1(int cnt, u32 *in)
{
	enum mlx5_monitor_counter_ppcnt ppcnt_cnt;

	for (ppcnt_cnt = 0;
	     ppcnt_cnt < NUM_REQ_PPCNT_COUNTER_S1;
	     ppcnt_cnt++, cnt++) {
		MLX5_SET(set_monitor_counter_in, in,
			 monitor_counter[cnt].type,
			 MLX5_QUERY_MONITOR_CNT_TYPE_PPCNT);
		MLX5_SET(set_monitor_counter_in, in,
			 monitor_counter[cnt].counter,
			 ppcnt_cnt);
	}
	return ppcnt_cnt;
}