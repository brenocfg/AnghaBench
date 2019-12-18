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
struct TYPE_2__ {int /*<<< orphan*/  counter_group_id; int /*<<< orphan*/  counter; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int MLX5_QUERY_MONITOR_CNT_TYPE_Q_COUNTER ; 
 int MLX5_QUERY_MONITOR_Q_COUNTER_RX_OUT_OF_BUFFER ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* monitor_counter ; 
 int /*<<< orphan*/  set_monitor_counter_in ; 

__attribute__((used)) static int fill_monitor_counter_q_counter_set1(int cnt, int q_counter, u32 *in)
{
	MLX5_SET(set_monitor_counter_in, in,
		 monitor_counter[cnt].type,
		 MLX5_QUERY_MONITOR_CNT_TYPE_Q_COUNTER);
	MLX5_SET(set_monitor_counter_in, in,
		 monitor_counter[cnt].counter,
		 MLX5_QUERY_MONITOR_Q_COUNTER_RX_OUT_OF_BUFFER);
	MLX5_SET(set_monitor_counter_in, in,
		 monitor_counter[cnt].counter_group_id,
		 q_counter);
	return 1;
}