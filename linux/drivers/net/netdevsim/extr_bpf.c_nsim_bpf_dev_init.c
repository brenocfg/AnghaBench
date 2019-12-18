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
struct nsim_dev {int bpf_bind_accept; int /*<<< orphan*/  bpf_bind_verifier_delay; int /*<<< orphan*/  ddir; int /*<<< orphan*/  bpf_dev; int /*<<< orphan*/  ddir_bpf_bound_progs; int /*<<< orphan*/  bpf_bound_maps; int /*<<< orphan*/  bpf_bound_progs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_offload_dev_create (int /*<<< orphan*/ *,struct nsim_dev*) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsim_bpf_dev_ops ; 

int nsim_bpf_dev_init(struct nsim_dev *nsim_dev)
{
	int err;

	INIT_LIST_HEAD(&nsim_dev->bpf_bound_progs);
	INIT_LIST_HEAD(&nsim_dev->bpf_bound_maps);

	nsim_dev->ddir_bpf_bound_progs = debugfs_create_dir("bpf_bound_progs",
							    nsim_dev->ddir);
	if (IS_ERR_OR_NULL(nsim_dev->ddir_bpf_bound_progs))
		return -ENOMEM;

	nsim_dev->bpf_dev = bpf_offload_dev_create(&nsim_bpf_dev_ops, nsim_dev);
	err = PTR_ERR_OR_ZERO(nsim_dev->bpf_dev);
	if (err)
		return err;

	nsim_dev->bpf_bind_accept = true;
	debugfs_create_bool("bpf_bind_accept", 0600, nsim_dev->ddir,
			    &nsim_dev->bpf_bind_accept);
	debugfs_create_u32("bpf_bind_verifier_delay", 0600, nsim_dev->ddir,
			   &nsim_dev->bpf_bind_verifier_delay);
	return 0;
}