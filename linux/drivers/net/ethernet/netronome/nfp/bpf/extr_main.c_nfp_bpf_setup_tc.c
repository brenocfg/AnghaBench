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
struct nfp_net {int dummy; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfp_net*,struct nfp_net*,int) ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_bpf_block_cb_list ; 
 int /*<<< orphan*/  nfp_bpf_setup_tc_block_cb ; 

__attribute__((used)) static int nfp_bpf_setup_tc(struct nfp_app *app, struct net_device *netdev,
			    enum tc_setup_type type, void *type_data)
{
	struct nfp_net *nn = netdev_priv(netdev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return flow_block_cb_setup_simple(type_data,
						  &nfp_bpf_block_cb_list,
						  nfp_bpf_setup_tc_block_cb,
						  nn, nn, true);
	default:
		return -EOPNOTSUPP;
	}
}