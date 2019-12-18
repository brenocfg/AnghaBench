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
struct nsim_dev {int /*<<< orphan*/  bpf_dev; int /*<<< orphan*/  bpf_bound_maps; int /*<<< orphan*/  bpf_bound_progs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bpf_offload_dev_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void nsim_bpf_dev_exit(struct nsim_dev *nsim_dev)
{
	WARN_ON(!list_empty(&nsim_dev->bpf_bound_progs));
	WARN_ON(!list_empty(&nsim_dev->bpf_bound_maps));
	bpf_offload_dev_destroy(nsim_dev->bpf_dev);
}