#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* name; int mode; } ;
struct TYPE_9__ {TYPE_4__ attr; int /*<<< orphan*/ * store; int /*<<< orphan*/  show; } ;
struct TYPE_8__ {TYPE_4__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct mlx4_port {scalar_t__ slave; TYPE_3__ smi_enabled; int /*<<< orphan*/  kobj; TYPE_2__ enable_smi_admin; TYPE_1__* dev; int /*<<< orphan*/  port_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 scalar_t__ mlx4_master_func_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_4__*) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  sysfs_show_enable_smi_admin ; 
 int /*<<< orphan*/  sysfs_show_smi_enabled ; 
 int /*<<< orphan*/  sysfs_store_enable_smi_admin ; 

__attribute__((used)) static int add_vf_smi_entries(struct mlx4_port *p)
{
	int is_eth = rdma_port_get_link_layer(&p->dev->ib_dev, p->port_num) ==
			IB_LINK_LAYER_ETHERNET;
	int ret;

	/* do not display entries if eth transport, or if master */
	if (is_eth || p->slave == mlx4_master_func_num(p->dev->dev))
		return 0;

	sysfs_attr_init(&p->smi_enabled.attr);
	p->smi_enabled.show = sysfs_show_smi_enabled;
	p->smi_enabled.store = NULL;
	p->smi_enabled.attr.name = "smi_enabled";
	p->smi_enabled.attr.mode = 0444;
	ret = sysfs_create_file(&p->kobj, &p->smi_enabled.attr);
	if (ret) {
		pr_err("failed to create smi_enabled\n");
		return ret;
	}

	sysfs_attr_init(&p->enable_smi_admin.attr);
	p->enable_smi_admin.show = sysfs_show_enable_smi_admin;
	p->enable_smi_admin.store = sysfs_store_enable_smi_admin;
	p->enable_smi_admin.attr.name = "enable_smi_admin";
	p->enable_smi_admin.attr.mode = 0644;
	ret = sysfs_create_file(&p->kobj, &p->enable_smi_admin.attr);
	if (ret) {
		pr_err("failed to create enable_smi_admin\n");
		sysfs_remove_file(&p->kobj, &p->smi_enabled.attr);
		return ret;
	}
	return 0;
}