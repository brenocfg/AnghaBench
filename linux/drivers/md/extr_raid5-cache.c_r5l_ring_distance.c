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
struct r5l_log {scalar_t__ device_size; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */

__attribute__((used)) static sector_t r5l_ring_distance(struct r5l_log *log, sector_t start,
				  sector_t end)
{
	if (end >= start)
		return end - start;
	else
		return end + log->device_size - start;
}