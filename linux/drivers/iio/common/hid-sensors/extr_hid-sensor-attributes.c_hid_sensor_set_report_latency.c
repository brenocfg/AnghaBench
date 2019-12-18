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
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  report_id; } ;
struct hid_sensor_common {TYPE_1__ report_latency; int /*<<< orphan*/  hsdev; } ;
typedef  int /*<<< orphan*/  latency_ms ;

/* Variables and functions */
 int sensor_hub_set_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

int hid_sensor_set_report_latency(struct hid_sensor_common *st, int latency_ms)
{
	return sensor_hub_set_feature(st->hsdev, st->report_latency.report_id,
				      st->report_latency.index,
				      sizeof(latency_ms), &latency_ms);
}