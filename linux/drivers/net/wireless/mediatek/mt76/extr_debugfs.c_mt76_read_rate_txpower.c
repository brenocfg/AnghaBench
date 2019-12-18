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
struct TYPE_2__ {int /*<<< orphan*/  vht; int /*<<< orphan*/  ht; int /*<<< orphan*/  stbc; int /*<<< orphan*/  ofdm; int /*<<< orphan*/  cck; } ;
struct mt76_dev {TYPE_1__ rate_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct mt76_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_seq_puts_array (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76_read_rate_txpower(struct seq_file *s, void *data)
{
	struct mt76_dev *dev = dev_get_drvdata(s->private);

	mt76_seq_puts_array(s, "CCK", dev->rate_power.cck,
			    ARRAY_SIZE(dev->rate_power.cck));
	mt76_seq_puts_array(s, "OFDM", dev->rate_power.ofdm,
			    ARRAY_SIZE(dev->rate_power.ofdm));
	mt76_seq_puts_array(s, "STBC", dev->rate_power.stbc,
			    ARRAY_SIZE(dev->rate_power.stbc));
	mt76_seq_puts_array(s, "HT", dev->rate_power.ht,
			    ARRAY_SIZE(dev->rate_power.ht));
	mt76_seq_puts_array(s, "VHT", dev->rate_power.vht,
			    ARRAY_SIZE(dev->rate_power.vht));
	return 0;
}