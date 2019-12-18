#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct dentry {int dummy; } ;
struct brcms_pub {struct dentry* dbgfs_dir; TYPE_3__* wlc; } ;
struct brcms_debugfs_entry {int (* read ) (struct seq_file*,void*) ;struct brcms_pub* drvr; } ;
struct TYPE_6__ {TYPE_2__* hw; } ;
struct TYPE_5__ {TYPE_1__* d11core; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brcms_debugfs_def_ops ; 
 int /*<<< orphan*/  debugfs_create_file (char const*,int,struct dentry*,struct brcms_debugfs_entry*,int /*<<< orphan*/ *) ; 
 struct brcms_debugfs_entry* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcms_debugfs_add_entry(struct brcms_pub *drvr, const char *fn,
			int (*read_fn)(struct seq_file *seq, void *data))
{
	struct device *dev = &drvr->wlc->hw->d11core->dev;
	struct dentry *dentry =  drvr->dbgfs_dir;
	struct brcms_debugfs_entry *entry;

	entry = devm_kzalloc(dev, sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return;

	entry->read = read_fn;
	entry->drvr = drvr;

	debugfs_create_file(fn, 0444, dentry, entry, &brcms_debugfs_def_ops);
}