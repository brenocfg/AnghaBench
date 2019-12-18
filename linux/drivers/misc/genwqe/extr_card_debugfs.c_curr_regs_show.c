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
struct genwqe_reg {int addr; int val; } ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int GENWQE_FFDC_REGS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  genwqe_read_ffdc_regs (struct genwqe_dev*,struct genwqe_reg*,unsigned int,int) ; 
 int /*<<< orphan*/  genwqe_start_traps (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_stop_traps (struct genwqe_dev*) ; 
 struct genwqe_reg* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 

__attribute__((used)) static int curr_regs_show(struct seq_file *s, void *unused)
{
	struct genwqe_dev *cd = s->private;
	unsigned int i;
	struct genwqe_reg *regs;

	regs = kcalloc(GENWQE_FFDC_REGS, sizeof(*regs), GFP_KERNEL);
	if (regs == NULL)
		return -ENOMEM;

	genwqe_stop_traps(cd);
	genwqe_read_ffdc_regs(cd, regs, GENWQE_FFDC_REGS, 1);
	genwqe_start_traps(cd);

	for (i = 0; i < GENWQE_FFDC_REGS; i++) {
		if (regs[i].addr == 0xffffffff)
			break;  /* invalid entries */

		if (regs[i].val == 0x0ull)
			continue;  /* do not print 0x0 FIRs */

		seq_printf(s, "  0x%08x 0x%016llx\n",
			   regs[i].addr, regs[i].val);
	}
	return 0;
}