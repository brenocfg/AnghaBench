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
struct seq_file {scalar_t__ size; struct inode* private; } ;
struct nubus_proc_pde_data {scalar_t__ res_size; scalar_t__ res_ptr; } ;
struct nubus_dirent {int mask; scalar_t__ data; scalar_t__ base; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EFBIG ; 
 struct nubus_proc_pde_data* PDE_DATA (struct inode*) ; 
 int /*<<< orphan*/  nubus_seq_write_rsrc_mem (struct seq_file*,struct nubus_dirent*,scalar_t__) ; 
 scalar_t__ proc_get_parent_data (struct inode*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,unsigned int) ; 

__attribute__((used)) static int nubus_proc_rsrc_show(struct seq_file *m, void *v)
{
	struct inode *inode = m->private;
	struct nubus_proc_pde_data *pde_data;

	pde_data = PDE_DATA(inode);
	if (!pde_data)
		return 0;

	if (pde_data->res_size > m->size)
		return -EFBIG;

	if (pde_data->res_size) {
		int lanes = (int)proc_get_parent_data(inode);
		struct nubus_dirent ent;

		if (!lanes)
			return 0;

		ent.mask = lanes;
		ent.base = pde_data->res_ptr;
		ent.data = 0;
		nubus_seq_write_rsrc_mem(m, &ent, pde_data->res_size);
	} else {
		unsigned int data = (unsigned int)pde_data->res_ptr;

		seq_putc(m, data >> 16);
		seq_putc(m, data >> 8);
		seq_putc(m, data >> 0);
	}
	return 0;
}