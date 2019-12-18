#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_output_handle {int dummy; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct list_head {int dummy; } ;
struct etm_event_data {int dummy; } ;
struct coresight_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* enable ) (struct coresight_device*,struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_PERF ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 scalar_t__ PERF_HES_STOPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  coresight_disable_path (struct list_head*) ; 
 scalar_t__ coresight_enable_path (struct list_head*,int /*<<< orphan*/ ,struct perf_output_handle*) ; 
 struct coresight_device* coresight_get_sink (struct list_head*) ; 
 int /*<<< orphan*/  csdev_src ; 
 int /*<<< orphan*/  ctx_handle ; 
 struct list_head* etm_event_cpu_path (struct etm_event_data*,int) ; 
 struct coresight_device* per_cpu (int /*<<< orphan*/ ,int) ; 
 struct etm_event_data* perf_aux_output_begin (struct perf_output_handle*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_aux_output_end (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 TYPE_2__* source_ops (struct coresight_device*) ; 
 scalar_t__ stub1 (struct coresight_device*,struct perf_event*,int /*<<< orphan*/ ) ; 
 struct perf_output_handle* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void etm_event_start(struct perf_event *event, int flags)
{
	int cpu = smp_processor_id();
	struct etm_event_data *event_data;
	struct perf_output_handle *handle = this_cpu_ptr(&ctx_handle);
	struct coresight_device *sink, *csdev = per_cpu(csdev_src, cpu);
	struct list_head *path;

	if (!csdev)
		goto fail;

	/*
	 * Deal with the ring buffer API and get a handle on the
	 * session's information.
	 */
	event_data = perf_aux_output_begin(handle, event);
	if (!event_data)
		goto fail;

	path = etm_event_cpu_path(event_data, cpu);
	/* We need a sink, no need to continue without one */
	sink = coresight_get_sink(path);
	if (WARN_ON_ONCE(!sink))
		goto fail_end_stop;

	/* Nothing will happen without a path */
	if (coresight_enable_path(path, CS_MODE_PERF, handle))
		goto fail_end_stop;

	/* Tell the perf core the event is alive */
	event->hw.state = 0;

	/* Finally enable the tracer */
	if (source_ops(csdev)->enable(csdev, event, CS_MODE_PERF))
		goto fail_disable_path;

out:
	return;

fail_disable_path:
	coresight_disable_path(path);
fail_end_stop:
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	perf_aux_output_end(handle, 0);
fail:
	event->hw.state = PERF_HES_STOPPED;
	goto out;
}