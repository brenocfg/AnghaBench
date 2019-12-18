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
struct rhashtable_compare_arg {struct nfp_fl_flow_table_cmp_arg* key; } ;
struct nfp_fl_payload {scalar_t__ ingress_dev; scalar_t__ tc_flower_cookie; } ;
struct nfp_fl_flow_table_cmp_arg {scalar_t__ netdev; scalar_t__ cookie; } ;

/* Variables and functions */

__attribute__((used)) static int nfp_fl_obj_cmpfn(struct rhashtable_compare_arg *arg,
			    const void *obj)
{
	const struct nfp_fl_flow_table_cmp_arg *cmp_arg = arg->key;
	const struct nfp_fl_payload *flow_entry = obj;

	if (flow_entry->ingress_dev == cmp_arg->netdev)
		return flow_entry->tc_flower_cookie != cmp_arg->cookie;

	return 1;
}