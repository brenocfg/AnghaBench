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
struct qede_arfs_tuple {scalar_t__ eth_proto; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool qede_flow_spec_ipv6_cmp(struct qede_arfs_tuple *a,
				    struct qede_arfs_tuple *b)
{
	if (a->eth_proto != htons(ETH_P_IPV6) ||
	    b->eth_proto != htons(ETH_P_IPV6))
		return false;

	if (memcmp(&a->src_ipv6, &b->src_ipv6, sizeof(struct in6_addr)))
		return false;

	if (memcmp(&a->dst_ipv6, &b->dst_ipv6, sizeof(struct in6_addr)))
		return false;

	return true;
}