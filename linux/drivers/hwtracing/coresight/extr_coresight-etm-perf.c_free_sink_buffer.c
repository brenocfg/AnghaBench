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
struct etm_event_data {int /*<<< orphan*/  snk_config; int /*<<< orphan*/  mask; } ;
struct coresight_device {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_buffer ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct coresight_device* coresight_get_sink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ *) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etm_event_cpu_path (struct etm_event_data*,int) ; 
 TYPE_1__* sink_ops (struct coresight_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_sink_buffer(struct etm_event_data *event_data)
{
	int cpu;
	cpumask_t *mask = &event_data->mask;
	struct coresight_device *sink;

	if (WARN_ON(cpumask_empty(mask)))
		return;

	if (!event_data->snk_config)
		return;

	cpu = cpumask_first(mask);
	sink = coresight_get_sink(etm_event_cpu_path(event_data, cpu));
	sink_ops(sink)->free_buffer(event_data->snk_config);
}