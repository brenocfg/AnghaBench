#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; int /*<<< orphan*/  width; int /*<<< orphan*/  period; int /*<<< orphan*/  n_pulses; } ;
struct mt7615_dev {TYPE_2__ mt76; TYPE_1__ radar_pattern; int /*<<< orphan*/  hw_pattern; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  debugfs_create_devm_seqfile (int /*<<< orphan*/ ,char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mt7615_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u16 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_radar_pattern ; 
 int /*<<< orphan*/  fops_scs ; 
 int /*<<< orphan*/  mt7615_radio_read ; 
 int /*<<< orphan*/  mt7615_read_temperature ; 
 struct dentry* mt76_register_debugfs (TYPE_2__*) ; 

int mt7615_init_debugfs(struct mt7615_dev *dev)
{
	struct dentry *dir;

	dir = mt76_register_debugfs(&dev->mt76);
	if (!dir)
		return -ENOMEM;

	debugfs_create_file("scs", 0600, dir, dev, &fops_scs);
	debugfs_create_devm_seqfile(dev->mt76.dev, "radio", dir,
				    mt7615_radio_read);
	debugfs_create_u32("dfs_hw_pattern", 0400, dir, &dev->hw_pattern);
	/* test pattern knobs */
	debugfs_create_u8("pattern_len", 0600, dir,
			  &dev->radar_pattern.n_pulses);
	debugfs_create_u32("pulse_period", 0600, dir,
			   &dev->radar_pattern.period);
	debugfs_create_u16("pulse_width", 0600, dir,
			   &dev->radar_pattern.width);
	debugfs_create_u16("pulse_power", 0600, dir,
			   &dev->radar_pattern.power);
	debugfs_create_file("radar_trigger", 0200, dir, dev,
			    &fops_radar_pattern);
	debugfs_create_devm_seqfile(dev->mt76.dev, "temperature", dir,
				    mt7615_read_temperature);

	return 0;
}