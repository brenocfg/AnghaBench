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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt7603_dev {TYPE_1__ mt76; int /*<<< orphan*/  reset_test; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_devm_seqfile (int /*<<< orphan*/ ,char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mt7603_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_edcca ; 
 int /*<<< orphan*/  mt7603_radio_read ; 
 int /*<<< orphan*/  mt7603_reset_read ; 
 struct dentry* mt76_register_debugfs (TYPE_1__*) ; 

void mt7603_init_debugfs(struct mt7603_dev *dev)
{
	struct dentry *dir;

	dir = mt76_register_debugfs(&dev->mt76);
	if (!dir)
		return;

	debugfs_create_file("edcca", 0600, dir, dev, &fops_edcca);
	debugfs_create_u32("reset_test", 0600, dir, &dev->reset_test);
	debugfs_create_devm_seqfile(dev->mt76.dev, "reset", dir,
				    mt7603_reset_read);
	debugfs_create_devm_seqfile(dev->mt76.dev, "radio", dir,
				    mt7603_radio_read);
}