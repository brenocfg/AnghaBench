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
struct log_c {int /*<<< orphan*/  sync_count; } ;
struct dm_dirty_log {scalar_t__ context; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */

__attribute__((used)) static region_t core_get_sync_count(struct dm_dirty_log *log)
{
        struct log_c *lc = (struct log_c *) log->context;

        return lc->sync_count;
}