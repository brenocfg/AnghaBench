#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {void* events_stat_aggregate; void* events_stat; } ;

/* Variables and functions */

void *goya_get_events_stat(struct hl_device *hdev, bool aggregate, u32 *size)
{
	struct goya_device *goya = hdev->asic_specific;

	if (aggregate) {
		*size = (u32) sizeof(goya->events_stat_aggregate);
		return goya->events_stat_aggregate;
	}

	*size = (u32) sizeof(goya->events_stat);
	return goya->events_stat;
}