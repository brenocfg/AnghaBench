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
struct seq_tab {scalar_t__ data; } ;
struct inode {struct adapter* i_private; } ;
struct file {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int DBGLAMODE_G (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int TPLA_SIZE ; 
 int /*<<< orphan*/  TP_DBG_LA_CONFIG_A ; 
 struct seq_tab* seq_open_tab (struct file*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_tp_read_la (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tp_la_show ; 
 int /*<<< orphan*/  tp_la_show2 ; 
 int /*<<< orphan*/  tp_la_show3 ; 

__attribute__((used)) static int tp_la_open(struct inode *inode, struct file *file)
{
	struct seq_tab *p;
	struct adapter *adap = inode->i_private;

	switch (DBGLAMODE_G(t4_read_reg(adap, TP_DBG_LA_CONFIG_A))) {
	case 2:
		p = seq_open_tab(file, TPLA_SIZE / 2, 2 * sizeof(u64), 0,
				 tp_la_show2);
		break;
	case 3:
		p = seq_open_tab(file, TPLA_SIZE / 2, 2 * sizeof(u64), 0,
				 tp_la_show3);
		break;
	default:
		p = seq_open_tab(file, TPLA_SIZE, sizeof(u64), 0, tp_la_show);
	}
	if (!p)
		return -ENOMEM;

	t4_tp_read_la(adap, (u64 *)p->data, NULL);
	return 0;
}