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
struct seq_file {int /*<<< orphan*/  private; } ;
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 struct mt7615_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int mt7615_mcu_get_temperature (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int mt7615_read_temperature(struct seq_file *s, void *data)
{
	struct mt7615_dev *dev = dev_get_drvdata(s->private);
	int temp;

	/* cpu */
	temp = mt7615_mcu_get_temperature(dev, 0);
	seq_printf(s, "Temperature: %d\n", temp);

	return 0;
}