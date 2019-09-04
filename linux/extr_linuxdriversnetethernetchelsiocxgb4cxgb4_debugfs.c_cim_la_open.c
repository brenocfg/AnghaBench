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
typedef  int /*<<< orphan*/  u32 ;
struct seq_tab {scalar_t__ data; } ;
struct inode {struct adapter* i_private; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int cim_la_size; int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int UPDBGLACAPTPCONLY_F ; 
 int /*<<< orphan*/  UP_UP_DBG_LA_CFG_A ; 
 int /*<<< orphan*/  cim_la_show ; 
 int /*<<< orphan*/  cim_la_show_3in1 ; 
 int /*<<< orphan*/  cim_la_show_pc_t6 ; 
 int /*<<< orphan*/  cim_la_show_t6 ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 struct seq_tab* seq_open_tab (struct file*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_release_private (struct inode*,struct file*) ; 
 int t4_cim_read (struct adapter*,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int t4_cim_read_la (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cim_la_open(struct inode *inode, struct file *file)
{
	int ret;
	unsigned int cfg;
	struct seq_tab *p;
	struct adapter *adap = inode->i_private;

	ret = t4_cim_read(adap, UP_UP_DBG_LA_CFG_A, 1, &cfg);
	if (ret)
		return ret;

	if (is_t6(adap->params.chip)) {
		/* +1 to account for integer division of CIMLA_SIZE/10 */
		p = seq_open_tab(file, (adap->params.cim_la_size / 10) + 1,
				 10 * sizeof(u32), 1,
				 cfg & UPDBGLACAPTPCONLY_F ?
					cim_la_show_pc_t6 : cim_la_show_t6);
	} else {
		p = seq_open_tab(file, adap->params.cim_la_size / 8,
				 8 * sizeof(u32), 1,
				 cfg & UPDBGLACAPTPCONLY_F ? cim_la_show_3in1 :
							     cim_la_show);
	}
	if (!p)
		return -ENOMEM;

	ret = t4_cim_read_la(adap, (u32 *)p->data, NULL);
	if (ret)
		seq_release_private(inode, file);
	return ret;
}