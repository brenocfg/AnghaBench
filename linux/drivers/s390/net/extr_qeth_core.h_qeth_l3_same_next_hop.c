#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ipv6_addr; } ;
struct qeth_hdr_layer3 {int flags; TYPE_1__ next_hop; } ;

/* Variables and functions */
 int QETH_HDR_IPV6 ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool qeth_l3_same_next_hop(struct qeth_hdr_layer3 *h1,
					 struct qeth_hdr_layer3 *h2)
{
	return !((h1->flags ^ h2->flags) & QETH_HDR_IPV6) &&
	       ipv6_addr_equal(&h1->next_hop.ipv6_addr,
			       &h2->next_hop.ipv6_addr);
}