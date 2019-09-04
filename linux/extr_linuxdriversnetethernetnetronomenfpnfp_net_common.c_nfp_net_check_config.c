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
struct nfp_net_dp {scalar_t__ fl_bufsz; scalar_t__ num_tx_rings; int /*<<< orphan*/  xdp_prog; } ;
struct nfp_net {scalar_t__ max_tx_rings; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static int
nfp_net_check_config(struct nfp_net *nn, struct nfp_net_dp *dp,
		     struct netlink_ext_ack *extack)
{
	/* XDP-enabled tests */
	if (!dp->xdp_prog)
		return 0;
	if (dp->fl_bufsz > PAGE_SIZE) {
		NL_SET_ERR_MSG_MOD(extack, "MTU too large w/ XDP enabled");
		return -EINVAL;
	}
	if (dp->num_tx_rings > nn->max_tx_rings) {
		NL_SET_ERR_MSG_MOD(extack, "Insufficient number of TX rings w/ XDP enabled");
		return -EINVAL;
	}

	return 0;
}