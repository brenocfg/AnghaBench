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
struct seq_file {scalar_t__ private; } ;
struct hfi1_ibdev {int dummy; } ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct hfi1_devdata* dd_from_dev (struct hfi1_ibdev*) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index_safe (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  seqfile_dump_rcd (struct seq_file*,struct hfi1_ctxtdata*) ; 

__attribute__((used)) static int _rcds_seq_show(struct seq_file *s, void *v)
{
	struct hfi1_ibdev *ibd = (struct hfi1_ibdev *)s->private;
	struct hfi1_devdata *dd = dd_from_dev(ibd);
	struct hfi1_ctxtdata *rcd;
	loff_t *spos = v;
	loff_t i = *spos;

	rcd = hfi1_rcd_get_by_index_safe(dd, i);
	if (rcd)
		seqfile_dump_rcd(s, rcd);
	hfi1_rcd_put(rcd);
	return 0;
}