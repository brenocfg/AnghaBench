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
struct smsdvb_debugfs {int stats_count; int /*<<< orphan*/  lock; scalar_t__ stats_was_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsdvb_stats_wait_read(struct smsdvb_debugfs *debug_data)
{
	int rc = 1;

	spin_lock(&debug_data->lock);

	if (debug_data->stats_was_read)
		goto exit;

	rc = debug_data->stats_count;

exit:
	spin_unlock(&debug_data->lock);
	return rc;
}