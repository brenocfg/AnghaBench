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
struct perf_output_handle {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct etm_event_data {int /*<<< orphan*/ * path; int /*<<< orphan*/  snk_config; } ;
struct coresight_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ (* set_buffer ) (struct coresight_device*,struct perf_output_handle*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ (* enable ) (struct coresight_device*,struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_PERF ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 scalar_t__ PERF_HES_STOPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ coresight_enable_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct coresight_device* coresight_get_sink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csdev_src ; 
 int /*<<< orphan*/  ctx_handle ; 
 struct coresight_device* per_cpu (int /*<<< orphan*/ ,int) ; 
 struct etm_event_data* perf_aux_output_begin (struct perf_output_handle*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_aux_output_end (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 TYPE_3__* sink_ops (struct coresight_device*) ; 
 int smp_processor_id () ; 
 TYPE_2__* source_ops (struct coresight_device*) ; 
 scalar_t__ stub1 (struct coresight_device*,struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct coresight_device*,struct perf_event*,int /*<<< orphan*/ ) ; 
 struct perf_output_handle* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void etm_event_start(struct perf_event *event, int flags)
{
	int cpu = smp_processor_id();
	struct etm_event_data *event_data;
	struct perf_output_handle *handle = this_cpu_ptr(&ctx_handle);
	struct coresight_device *sink, *csdev = per_cpu(csdev_src, cpu);

	if (!csdev)
		goto fail;

	/*
	 * Deal with the ring buffer API and get a handle on the
	 * session's information.
	 */
	event_data = perf_aux_output_begin(handle, event);
	if (!event_data)
		goto fail;

	/* We need a sink, no need to continue without one */
	sink = coresight_get_sink(event_data->path[cpu]);
	if (WARN_ON_ONCE(!sink || !sink_ops(sink)->set_buffer))
		goto fail_end_stop;

	/* Configure the sink */
	if (sink_ops(sink)->set_buffer(sink, handle,
				       event_data->snk_config))
		goto fail_end_stop;

	/* Nothing will happen without a path */
	if (coresight_enable_path(event_data->path[cpu], CS_MODE_PERF))
		goto fail_end_stop;

	/* Tell the perf core the event is alive */
	event->hw.state = 0;

	/* Finally enable the tracer */
	if (source_ops(csdev)->enable(csdev, event, CS_MODE_PERF))
		goto fail_end_stop;

out:
	return;

fail_end_stop:
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	perf_aux_output_end(handle, 0);
fail:
	event->hw.state = PERF_HES_STOPPED;
	goto out;
}