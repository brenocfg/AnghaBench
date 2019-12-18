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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ timestamp; } ;
struct tracer_event {TYPE_1__ timestamp_event; } ;
struct mlx5_fw_tracer {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_GET (struct tracer_event,scalar_t__*,scalar_t__) ; 
 scalar_t__ TRACER_EVENT_TYPE_TIMESTAMP ; 
 int /*<<< orphan*/  poll_trace (struct mlx5_fw_tracer*,struct tracer_event*,scalar_t__*) ; 

__attribute__((used)) static u64 get_block_timestamp(struct mlx5_fw_tracer *tracer, u64 *ts_event)
{
	struct tracer_event tracer_event;
	u8 event_id;

	event_id = MLX5_GET(tracer_event, ts_event, event_id);

	if (event_id == TRACER_EVENT_TYPE_TIMESTAMP)
		poll_trace(tracer, &tracer_event, ts_event);
	else
		tracer_event.timestamp_event.timestamp = 0;

	return tracer_event.timestamp_event.timestamp;
}