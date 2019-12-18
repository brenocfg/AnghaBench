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
struct r5l_log {scalar_t__ device_size; int /*<<< orphan*/  log_start; int /*<<< orphan*/  last_checkpoint; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ r5l_ring_distance (struct r5l_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r5l_has_free_space(struct r5l_log *log, sector_t size)
{
	sector_t used_size;

	used_size = r5l_ring_distance(log, log->last_checkpoint,
					log->log_start);

	return log->device_size > used_size + size;
}