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
struct nfp_net {int /*<<< orphan*/  xdp_hw; int /*<<< orphan*/  app; } ;
struct netdev_bpf {int /*<<< orphan*/  extack; int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int EBUSY ; 
 int nfp_app_xdp_offload (int /*<<< orphan*/ ,struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_attachment_flags_ok (int /*<<< orphan*/ *,struct netdev_bpf*) ; 
 int /*<<< orphan*/  xdp_attachment_setup (int /*<<< orphan*/ *,struct netdev_bpf*) ; 

__attribute__((used)) static int nfp_net_xdp_setup_hw(struct nfp_net *nn, struct netdev_bpf *bpf)
{
	int err;

	if (!xdp_attachment_flags_ok(&nn->xdp_hw, bpf))
		return -EBUSY;

	err = nfp_app_xdp_offload(nn->app, nn, bpf->prog, bpf->extack);
	if (err)
		return err;

	xdp_attachment_setup(&nn->xdp_hw, bpf);
	return 0;
}