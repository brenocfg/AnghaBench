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
typedef  int /*<<< orphan*/  u32 ;
struct seq_tab {scalar_t__ data; } ;
struct inode {struct adapter* i_private; } ;
struct file {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CIM_PIFLA_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cim_pif_la_show ; 
 struct seq_tab* seq_open_tab (struct file*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_cim_read_pif_la (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cim_pif_la_open(struct inode *inode, struct file *file)
{
	struct seq_tab *p;
	struct adapter *adap = inode->i_private;

	p = seq_open_tab(file, 2 * CIM_PIFLA_SIZE, 6 * sizeof(u32), 1,
			 cim_pif_la_show);
	if (!p)
		return -ENOMEM;

	t4_cim_read_pif_la(adap, (u32 *)p->data,
			   (u32 *)p->data + 6 * CIM_PIFLA_SIZE, NULL, NULL);
	return 0;
}