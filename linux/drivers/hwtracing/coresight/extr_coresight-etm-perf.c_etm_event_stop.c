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
struct perf_output_handle {struct perf_event* event; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct list_head {int dummy; } ;
struct etm_event_data {int /*<<< orphan*/  snk_config; } ;
struct coresight_device {int dummy; } ;
struct TYPE_6__ {unsigned long (* update_buffer ) (struct coresight_device*,struct perf_output_handle*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* disable ) (struct coresight_device*,struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 scalar_t__ PERF_HES_STOPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  coresight_disable_path (struct list_head*) ; 
 struct coresight_device* coresight_get_sink (struct list_head*) ; 
 int /*<<< orphan*/  csdev_src ; 
 int /*<<< orphan*/  ctx_handle ; 
 struct list_head* etm_event_cpu_path (struct etm_event_data*,int) ; 
 struct coresight_device* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_aux_output_end (struct perf_output_handle*,unsigned long) ; 
 struct etm_event_data* perf_get_aux (struct perf_output_handle*) ; 
 TYPE_3__* sink_ops (struct coresight_device*) ; 
 int smp_processor_id () ; 
 TYPE_2__* source_ops (struct coresight_device*) ; 
 int /*<<< orphan*/  stub1 (struct coresight_device*,struct perf_event*) ; 
 unsigned long stub2 (struct coresight_device*,struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 struct perf_output_handle* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void etm_event_stop(struct perf_event *event, int mode)
{
	int cpu = smp_processor_id();
	unsigned long size;
	struct coresight_device *sink, *csdev = per_cpu(csdev_src, cpu);
	struct perf_output_handle *handle = this_cpu_ptr(&ctx_handle);
	struct etm_event_data *event_data = perf_get_aux(handle);
	struct list_head *path;

	if (event->hw.state == PERF_HES_STOPPED)
		return;

	if (!csdev)
		return;

	path = etm_event_cpu_path(event_data, cpu);
	if (!path)
		return;

	sink = coresight_get_sink(path);
	if (!sink)
		return;

	/* stop tracer */
	source_ops(csdev)->disable(csdev, event);

	/* tell the core */
	event->hw.state = PERF_HES_STOPPED;

	if (mode & PERF_EF_UPDATE) {
		if (WARN_ON_ONCE(handle->event != event))
			return;

		/* update trace information */
		if (!sink_ops(sink)->update_buffer)
			return;

		size = sink_ops(sink)->update_buffer(sink, handle,
					      event_data->snk_config);
		perf_aux_output_end(handle, size);
	}

	/* Disabling the path make its elements available to other sessions */
	coresight_disable_path(path);
}