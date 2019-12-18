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
struct seq_file {int /*<<< orphan*/  private; } ;
struct TYPE_2__ {int /*<<< orphan*/  agc_gain_adjust; int /*<<< orphan*/  false_cca; int /*<<< orphan*/  low_gain; int /*<<< orphan*/  avg_rssi_all; } ;
struct mt76x02_dev {TYPE_1__ cal; } ;

/* Variables and functions */
 struct mt76x02_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_agc(struct seq_file *file, void *data)
{
	struct mt76x02_dev *dev = dev_get_drvdata(file->private);

	seq_printf(file, "avg_rssi: %d\n", dev->cal.avg_rssi_all);
	seq_printf(file, "low_gain: %d\n", dev->cal.low_gain);
	seq_printf(file, "false_cca: %d\n", dev->cal.false_cca);
	seq_printf(file, "agc_gain_adjust: %d\n", dev->cal.agc_gain_adjust);

	return 0;
}