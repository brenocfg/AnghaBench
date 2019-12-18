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
struct vc4_dev {int /*<<< orphan*/  debugfs_list; } ;
struct TYPE_2__ {char const* name; int (* show ) (struct seq_file*,void*) ;void* data; } ;
struct vc4_debugfs_info_entry {int /*<<< orphan*/  link; TYPE_1__ info; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vc4_debugfs_info_entry* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

void vc4_debugfs_add_file(struct drm_device *dev,
			  const char *name,
			  int (*show)(struct seq_file*, void*),
			  void *data)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	struct vc4_debugfs_info_entry *entry =
		devm_kzalloc(dev->dev, sizeof(*entry), GFP_KERNEL);

	if (!entry)
		return;

	entry->info.name = name;
	entry->info.show = show;
	entry->info.data = data;

	list_add(&entry->link, &vc4->debugfs_list);
}