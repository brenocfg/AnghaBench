#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_8__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_10__ {TYPE_4__ v6addrs; TYPE_3__ v4addrs; } ;
struct TYPE_7__ {scalar_t__ n_proto; } ;
struct TYPE_6__ {scalar_t__ src; scalar_t__ dst; } ;
struct flow_keys {TYPE_5__ addrs; TYPE_2__ basic; TYPE_1__ ports; } ;
struct arfs_tuple {scalar_t__ src_port; scalar_t__ dst_port; scalar_t__ etype; scalar_t__ src_ipv4; scalar_t__ dst_ipv4; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool arfs_cmp(const struct arfs_tuple *tuple, const struct flow_keys *fk)
{
	if (tuple->src_port != fk->ports.src || tuple->dst_port != fk->ports.dst)
		return false;
	if (tuple->etype != fk->basic.n_proto)
		return false;
	if (tuple->etype == htons(ETH_P_IP))
		return tuple->src_ipv4 == fk->addrs.v4addrs.src &&
		       tuple->dst_ipv4 == fk->addrs.v4addrs.dst;
	if (tuple->etype == htons(ETH_P_IPV6))
		return !memcmp(&tuple->src_ipv6, &fk->addrs.v6addrs.src,
			       sizeof(struct in6_addr)) &&
		       !memcmp(&tuple->dst_ipv6, &fk->addrs.v6addrs.dst,
			       sizeof(struct in6_addr));
	return false;
}