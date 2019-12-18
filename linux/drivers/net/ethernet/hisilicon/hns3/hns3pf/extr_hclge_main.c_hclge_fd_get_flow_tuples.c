#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct hclge_fd_rule_tuples {void** dst_ip; void** src_ip; void* dst_port; int /*<<< orphan*/  ip_proto; void* ether_proto; } ;
struct TYPE_15__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_16__ {TYPE_6__ in6_u; } ;
struct TYPE_13__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_14__ {TYPE_4__ in6_u; } ;
struct TYPE_17__ {TYPE_7__ dst; TYPE_5__ src; } ;
struct TYPE_12__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_18__ {TYPE_8__ v6addrs; TYPE_3__ v4addrs; } ;
struct TYPE_11__ {scalar_t__ n_proto; int /*<<< orphan*/  ip_proto; } ;
struct TYPE_10__ {scalar_t__ dst; } ;
struct flow_keys {TYPE_9__ addrs; TYPE_2__ basic; TYPE_1__ ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 void* be16_to_cpu (scalar_t__) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_fd_get_flow_tuples(const struct flow_keys *fkeys,
				     struct hclge_fd_rule_tuples *tuples)
{
	tuples->ether_proto = be16_to_cpu(fkeys->basic.n_proto);
	tuples->ip_proto = fkeys->basic.ip_proto;
	tuples->dst_port = be16_to_cpu(fkeys->ports.dst);

	if (fkeys->basic.n_proto == htons(ETH_P_IP)) {
		tuples->src_ip[3] = be32_to_cpu(fkeys->addrs.v4addrs.src);
		tuples->dst_ip[3] = be32_to_cpu(fkeys->addrs.v4addrs.dst);
	} else {
		memcpy(tuples->src_ip,
		       fkeys->addrs.v6addrs.src.in6_u.u6_addr32,
		       sizeof(tuples->src_ip));
		memcpy(tuples->dst_ip,
		       fkeys->addrs.v6addrs.dst.in6_u.u6_addr32,
		       sizeof(tuples->dst_ip));
	}
}