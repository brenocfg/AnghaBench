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
struct seq_file {struct genwqe_dev* private; } ;
struct genwqe_dev {TYPE_1__* ffdc; } ;
struct TYPE_2__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_uidn_show (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prev_dbg_uidn_show(struct seq_file *s, void *unused, int uid)
{
	struct genwqe_dev *cd = s->private;

	dbg_uidn_show(s, cd->ffdc[uid].regs,  cd->ffdc[uid].entries);
	return 0;
}