#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netdevsim {int bpf_tc_accept; int bpf_tc_non_bound_accept; int bpf_xdpdrv_accept; int bpf_xdpoffload_accept; int bpf_map_accept; int /*<<< orphan*/  bpf_offloaded_id; int /*<<< orphan*/  netdev; TYPE_2__* nsim_dev; TYPE_1__* nsim_dev_port; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bpf_dev; } ;
struct TYPE_3__ {struct dentry* ddir; } ;

/* Variables and functions */
 int bpf_offload_dev_netdev_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int*) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 

int nsim_bpf_init(struct netdevsim *ns)
{
	struct dentry *ddir = ns->nsim_dev_port->ddir;
	int err;

	err = bpf_offload_dev_netdev_register(ns->nsim_dev->bpf_dev,
					      ns->netdev);
	if (err)
		return err;

	debugfs_create_u32("bpf_offloaded_id", 0400, ddir,
			   &ns->bpf_offloaded_id);

	ns->bpf_tc_accept = true;
	debugfs_create_bool("bpf_tc_accept", 0600, ddir,
			    &ns->bpf_tc_accept);
	debugfs_create_bool("bpf_tc_non_bound_accept", 0600, ddir,
			    &ns->bpf_tc_non_bound_accept);
	ns->bpf_xdpdrv_accept = true;
	debugfs_create_bool("bpf_xdpdrv_accept", 0600, ddir,
			    &ns->bpf_xdpdrv_accept);
	ns->bpf_xdpoffload_accept = true;
	debugfs_create_bool("bpf_xdpoffload_accept", 0600, ddir,
			    &ns->bpf_xdpoffload_accept);

	ns->bpf_map_accept = true;
	debugfs_create_bool("bpf_map_accept", 0600, ddir,
			    &ns->bpf_map_accept);

	return 0;
}