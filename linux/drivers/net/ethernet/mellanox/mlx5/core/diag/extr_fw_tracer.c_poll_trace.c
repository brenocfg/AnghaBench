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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_6__ {void* tdsn; void* tmsn; void* string_param; void* timestamp; } ;
struct TYPE_4__ {int unreliable; int timestamp; } ;
struct tracer_event {int event_id; int type; TYPE_3__ string_event; TYPE_1__ timestamp_event; void* lost_event; } ;
struct TYPE_5__ {int first_string_trace; int num_string_trace; } ;
struct mlx5_fw_tracer {TYPE_2__ str_db; int /*<<< orphan*/  trc_ver; } ;

/* Variables and functions */
 void* MLX5_GET (struct tracer_event*,int*,int) ; 
 int TRACER_EVENT_TYPE_STRING ; 
#define  TRACER_EVENT_TYPE_TIMESTAMP 128 
 int TRACER_EVENT_TYPE_UNRECOGNIZED ; 
 int event_id ; 
 int lost ; 
 int string_param ; 
 int tdsn ; 
 int timestamp ; 
 int timestamp39_8 ; 
 int timestamp52_40 ; 
 int timestamp7_0 ; 
 int tmsn ; 
 struct tracer_event* tracer_string_event ; 
 struct tracer_event* tracer_timestamp_event ; 

__attribute__((used)) static void poll_trace(struct mlx5_fw_tracer *tracer,
		       struct tracer_event *tracer_event, u64 *trace)
{
	u32 timestamp_low, timestamp_mid, timestamp_high, urts;

	tracer_event->event_id = MLX5_GET(tracer_event, trace, event_id);
	tracer_event->lost_event = MLX5_GET(tracer_event, trace, lost);

	switch (tracer_event->event_id) {
	case TRACER_EVENT_TYPE_TIMESTAMP:
		tracer_event->type = TRACER_EVENT_TYPE_TIMESTAMP;
		urts = MLX5_GET(tracer_timestamp_event, trace, urts);
		if (tracer->trc_ver == 0)
			tracer_event->timestamp_event.unreliable = !!(urts >> 2);
		else
			tracer_event->timestamp_event.unreliable = !!(urts & 1);

		timestamp_low = MLX5_GET(tracer_timestamp_event,
					 trace, timestamp7_0);
		timestamp_mid = MLX5_GET(tracer_timestamp_event,
					 trace, timestamp39_8);
		timestamp_high = MLX5_GET(tracer_timestamp_event,
					  trace, timestamp52_40);

		tracer_event->timestamp_event.timestamp =
				((u64)timestamp_high << 40) |
				((u64)timestamp_mid << 8) |
				(u64)timestamp_low;
		break;
	default:
		if (tracer_event->event_id >= tracer->str_db.first_string_trace ||
		    tracer_event->event_id <= tracer->str_db.first_string_trace +
					      tracer->str_db.num_string_trace) {
			tracer_event->type = TRACER_EVENT_TYPE_STRING;
			tracer_event->string_event.timestamp =
				MLX5_GET(tracer_string_event, trace, timestamp);
			tracer_event->string_event.string_param =
				MLX5_GET(tracer_string_event, trace, string_param);
			tracer_event->string_event.tmsn =
				MLX5_GET(tracer_string_event, trace, tmsn);
			tracer_event->string_event.tdsn =
				MLX5_GET(tracer_string_event, trace, tdsn);
		} else {
			tracer_event->type = TRACER_EVENT_TYPE_UNRECOGNIZED;
		}
		break;
	}
}