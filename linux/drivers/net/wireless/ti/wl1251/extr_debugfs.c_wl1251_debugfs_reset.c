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
struct TYPE_2__ {scalar_t__ excessive_retries; scalar_t__ retry_count; int /*<<< orphan*/ * fw_stats; } ;
struct wl1251 {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void wl1251_debugfs_reset(struct wl1251 *wl)
{
	if (wl->stats.fw_stats != NULL)
		memset(wl->stats.fw_stats, 0, sizeof(*wl->stats.fw_stats));
	wl->stats.retry_count = 0;
	wl->stats.excessive_retries = 0;
}