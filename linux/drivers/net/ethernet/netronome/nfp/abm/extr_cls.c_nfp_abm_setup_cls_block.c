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
struct nfp_repr {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_block_offload {int dummy; } ;

/* Variables and functions */
 int flow_block_cb_setup_simple (struct flow_block_offload*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfp_repr*,struct nfp_repr*,int) ; 
 int /*<<< orphan*/  nfp_abm_block_cb_list ; 
 int /*<<< orphan*/  nfp_abm_setup_tc_block_cb ; 

int nfp_abm_setup_cls_block(struct net_device *netdev, struct nfp_repr *repr,
			    struct flow_block_offload *f)
{
	return flow_block_cb_setup_simple(f, &nfp_abm_block_cb_list,
					  nfp_abm_setup_tc_block_cb,
					  repr, repr, true);
}