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
struct seq_file {struct hl_debugfs_entry* private; } ;
struct hl_device {TYPE_1__* asic_funcs; } ;
struct hl_debugfs_entry {struct hl_dbg_device_entry* dev_entry; } ;
struct hl_dbg_device_entry {struct hl_device* hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_device_idle ) (struct hl_device*,int /*<<< orphan*/ *,struct seq_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ *,struct seq_file*) ; 

__attribute__((used)) static int engines_show(struct seq_file *s, void *data)
{
	struct hl_debugfs_entry *entry = s->private;
	struct hl_dbg_device_entry *dev_entry = entry->dev_entry;
	struct hl_device *hdev = dev_entry->hdev;

	hdev->asic_funcs->is_device_idle(hdev, NULL, s);

	return 0;
}