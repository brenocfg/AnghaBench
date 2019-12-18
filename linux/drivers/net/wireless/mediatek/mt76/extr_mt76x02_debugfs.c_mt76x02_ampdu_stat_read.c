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
struct seq_file {struct mt76x02_dev* private; } ;
struct mt76x02_dev {int* aggr_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
mt76x02_ampdu_stat_read(struct seq_file *file, void *data)
{
	struct mt76x02_dev *dev = file->private;
	int i, j;

	for (i = 0; i < 4; i++) {
		seq_puts(file, "Length: ");
		for (j = 0; j < 8; j++)
			seq_printf(file, "%8d | ", i * 8 + j + 1);
		seq_puts(file, "\n");
		seq_puts(file, "Count:  ");
		for (j = 0; j < 8; j++)
			seq_printf(file, "%8d | ", dev->aggr_stats[i * 8 + j]);
		seq_puts(file, "\n");
		seq_puts(file, "--------");
		for (j = 0; j < 8; j++)
			seq_puts(file, "-----------");
		seq_puts(file, "\n");
	}

	return 0;
}