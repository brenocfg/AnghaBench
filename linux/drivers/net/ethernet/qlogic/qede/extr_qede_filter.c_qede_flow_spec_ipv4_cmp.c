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
struct qede_arfs_tuple {scalar_t__ eth_proto; scalar_t__ src_ipv4; scalar_t__ dst_ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qede_flow_spec_ipv4_cmp(struct qede_arfs_tuple *a,
				    struct qede_arfs_tuple *b)
{
	if (a->eth_proto != htons(ETH_P_IP) ||
	    b->eth_proto != htons(ETH_P_IP))
		return false;

	return (a->src_ipv4 == b->src_ipv4) &&
	       (a->dst_ipv4 == b->dst_ipv4);
}