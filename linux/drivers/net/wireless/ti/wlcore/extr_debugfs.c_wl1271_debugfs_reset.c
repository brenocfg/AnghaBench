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
struct TYPE_2__ {scalar_t__ excessive_retries; scalar_t__ retry_count; int /*<<< orphan*/  fw_stats_len; int /*<<< orphan*/  fw_stats; } ;
struct wl1271 {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wl1271_debugfs_reset(struct wl1271 *wl)
{
	if (!wl->stats.fw_stats)
		return;

	memset(wl->stats.fw_stats, 0, wl->stats.fw_stats_len);
	wl->stats.retry_count = 0;
	wl->stats.excessive_retries = 0;
}