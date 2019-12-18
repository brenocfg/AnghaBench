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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {struct genwqe_dev* private; } ;
struct genwqe_dev {unsigned int num_vfs; int /*<<< orphan*/ * vf_jobtimeout_msec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENWQE_PF_JOBTIMEOUT_MSEC ; 
 int /*<<< orphan*/  IO_SLC_VF_APPJOB_TIMEOUT ; 
 int /*<<< orphan*/  genwqe_read_vreg (struct genwqe_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int jtimer_show(struct seq_file *s, void *unused)
{
	struct genwqe_dev *cd = s->private;
	unsigned int vf_num;
	u64 jtimer;

	jtimer = genwqe_read_vreg(cd, IO_SLC_VF_APPJOB_TIMEOUT, 0);
	seq_printf(s, "  PF   0x%016llx %d msec\n", jtimer,
		   GENWQE_PF_JOBTIMEOUT_MSEC);

	for (vf_num = 0; vf_num < cd->num_vfs; vf_num++) {
		jtimer = genwqe_read_vreg(cd, IO_SLC_VF_APPJOB_TIMEOUT,
					  vf_num + 1);
		seq_printf(s, "  VF%-2d 0x%016llx %d msec\n", vf_num, jtimer,
			   cd->vf_jobtimeout_msec[vf_num]);
	}
	return 0;
}