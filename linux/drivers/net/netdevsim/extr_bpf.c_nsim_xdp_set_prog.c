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
struct xdp_attachment_info {int dummy; } ;
struct netdevsim {int /*<<< orphan*/  bpf_xdpoffload_accept; int /*<<< orphan*/  bpf_xdpdrv_accept; } ;
struct netdev_bpf {scalar_t__ command; int /*<<< orphan*/  extack; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NSIM_EA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ XDP_SETUP_PROG ; 
 scalar_t__ XDP_SETUP_PROG_HW ; 
 int nsim_xdp_offload_prog (struct netdevsim*,struct netdev_bpf*) ; 
 int /*<<< orphan*/  xdp_attachment_flags_ok (struct xdp_attachment_info*,struct netdev_bpf*) ; 
 int /*<<< orphan*/  xdp_attachment_setup (struct xdp_attachment_info*,struct netdev_bpf*) ; 

__attribute__((used)) static int
nsim_xdp_set_prog(struct netdevsim *ns, struct netdev_bpf *bpf,
		  struct xdp_attachment_info *xdp)
{
	int err;

	if (!xdp_attachment_flags_ok(xdp, bpf))
		return -EBUSY;

	if (bpf->command == XDP_SETUP_PROG && !ns->bpf_xdpdrv_accept) {
		NSIM_EA(bpf->extack, "driver XDP disabled in DebugFS");
		return -EOPNOTSUPP;
	}
	if (bpf->command == XDP_SETUP_PROG_HW && !ns->bpf_xdpoffload_accept) {
		NSIM_EA(bpf->extack, "XDP offload disabled in DebugFS");
		return -EOPNOTSUPP;
	}

	if (bpf->command == XDP_SETUP_PROG_HW) {
		err = nsim_xdp_offload_prog(ns, bpf);
		if (err)
			return err;
	}

	xdp_attachment_setup(xdp, bpf);

	return 0;
}