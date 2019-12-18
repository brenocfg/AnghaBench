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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {size_t saved_traces_index; int /*<<< orphan*/  lock; struct mlx5_fw_trace_data* straces; } ;
struct mlx5_fw_tracer {TYPE_1__ st_arr; } ;
struct mlx5_fw_trace_data {int lost; int /*<<< orphan*/  msg; int /*<<< orphan*/  event_id; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 int SAVED_TRACES_NUM ; 
 int /*<<< orphan*/  TRACE_STR_MSG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy_pad (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_fw_tracer_save_trace(struct mlx5_fw_tracer *tracer,
				      u64 timestamp, bool lost,
				      u8 event_id, char *msg)
{
	struct mlx5_fw_trace_data *trace_data;

	mutex_lock(&tracer->st_arr.lock);
	trace_data = &tracer->st_arr.straces[tracer->st_arr.saved_traces_index];
	trace_data->timestamp = timestamp;
	trace_data->lost = lost;
	trace_data->event_id = event_id;
	strscpy_pad(trace_data->msg, msg, TRACE_STR_MSG);

	tracer->st_arr.saved_traces_index =
		(tracer->st_arr.saved_traces_index + 1) & (SAVED_TRACES_NUM - 1);
	mutex_unlock(&tracer->st_arr.lock);
}