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
struct seq_file {struct genwqe_dev* private; } ;
struct genwqe_reg {int dummy; } ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dbg_uidn_show (struct seq_file*,struct genwqe_reg*,int) ; 
 int /*<<< orphan*/  genwqe_ffdc_buff_read (struct genwqe_dev*,int,struct genwqe_reg*,int) ; 
 int genwqe_ffdc_buff_size (struct genwqe_dev*,int) ; 
 int /*<<< orphan*/  genwqe_start_traps (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_stop_traps (struct genwqe_dev*) ; 
 struct genwqe_reg* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct genwqe_reg*) ; 

__attribute__((used)) static int curr_dbg_uidn_show(struct seq_file *s, void *unused, int uid)
{
	struct genwqe_dev *cd = s->private;
	int entries;
	struct genwqe_reg *regs;

	entries = genwqe_ffdc_buff_size(cd, uid);
	if (entries < 0)
		return -EINVAL;

	if (entries == 0)
		return 0;

	regs = kcalloc(entries, sizeof(*regs), GFP_KERNEL);
	if (regs == NULL)
		return -ENOMEM;

	genwqe_stop_traps(cd); /* halt the traps while dumping data */
	genwqe_ffdc_buff_read(cd, uid, regs, entries);
	genwqe_start_traps(cd);

	dbg_uidn_show(s, regs, entries);
	kfree(regs);
	return 0;
}