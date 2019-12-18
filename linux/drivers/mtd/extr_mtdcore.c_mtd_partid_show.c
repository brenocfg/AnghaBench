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
struct seq_file {struct mtd_info* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  partid; } ;
struct mtd_info {TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtd_partid_show(struct seq_file *s, void *p)
{
	struct mtd_info *mtd = s->private;

	seq_printf(s, "%s\n", mtd->dbg.partid);

	return 0;
}