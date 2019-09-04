#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int dummy; } ;
struct TYPE_4__ {void* proc_d_l1_down; void* proc_grp_opt; void* proc_info; void* proc_adapter_dir; int /*<<< orphan*/  controller; } ;
typedef  TYPE_1__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRC (char*) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 char* adapter_dir_name ; 
 int /*<<< orphan*/  d_l1_down_proc_fops ; 
 int /*<<< orphan*/  d_l1_down_proc_name ; 
 int /*<<< orphan*/  grp_opt_proc_fops ; 
 int /*<<< orphan*/  grp_opt_proc_name ; 
 int /*<<< orphan*/  info_proc_fops ; 
 int /*<<< orphan*/  info_proc_name ; 
 struct proc_dir_entry* proc_create_data (int /*<<< orphan*/ ,int,struct proc_dir_entry*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct proc_dir_entry* proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_net_eicon ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 

int create_adapter_proc(diva_os_xdi_adapter_t *a)
{
	struct proc_dir_entry *de, *pe;
	char tmp[16];

	sprintf(tmp, "%s%d", adapter_dir_name, a->controller);
	if (!(de = proc_mkdir(tmp, proc_net_eicon)))
		return (0);
	a->proc_adapter_dir = (void *) de;

	pe = proc_create_data(info_proc_name, S_IRUGO | S_IWUSR, de,
			      &info_proc_fops, a);
	if (!pe)
		return (0);
	a->proc_info = (void *) pe;

	pe = proc_create_data(grp_opt_proc_name, S_IRUGO | S_IWUSR, de,
			      &grp_opt_proc_fops, a);
	if (pe)
		a->proc_grp_opt = (void *) pe;
	pe = proc_create_data(d_l1_down_proc_name, S_IRUGO | S_IWUSR, de,
			      &d_l1_down_proc_fops, a);
	if (pe)
		a->proc_d_l1_down = (void *) pe;

	DBG_TRC(("proc entry %s created", tmp));

	return (1);
}