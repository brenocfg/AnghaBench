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
struct seq_file {struct gb_loopback* private; } ;
struct gb_loopback {int /*<<< orphan*/  mutex; int /*<<< orphan*/  kfifo_lat; } ;

/* Variables and functions */
 int gb_loopback_dbgfs_latency_show_common (struct seq_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_loopback_dbgfs_latency_show(struct seq_file *s, void *unused)
{
	struct gb_loopback *gb = s->private;

	return gb_loopback_dbgfs_latency_show_common(s, &gb->kfifo_lat,
						     &gb->mutex);
}