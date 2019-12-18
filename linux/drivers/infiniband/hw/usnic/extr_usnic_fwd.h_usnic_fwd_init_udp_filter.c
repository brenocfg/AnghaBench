#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ dst_port; int /*<<< orphan*/  flags; scalar_t__ dst_addr; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;
struct filter {TYPE_2__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_FIELD_5TUP_DST_AD ; 
 int /*<<< orphan*/  FILTER_FIELD_5TUP_DST_PT ; 
 int /*<<< orphan*/  FILTER_FIELD_5TUP_PROTO ; 
 int /*<<< orphan*/  FILTER_IPV4_5TUPLE ; 
 int /*<<< orphan*/  PROTO_UDP ; 

__attribute__((used)) static inline void usnic_fwd_init_udp_filter(struct filter *filter,
						uint32_t daddr, uint16_t dport)
{
	filter->type = FILTER_IPV4_5TUPLE;
	filter->u.ipv4.flags = FILTER_FIELD_5TUP_PROTO;
	filter->u.ipv4.protocol = PROTO_UDP;

	if (daddr) {
		filter->u.ipv4.flags |= FILTER_FIELD_5TUP_DST_AD;
		filter->u.ipv4.dst_addr = daddr;
	}

	if (dport) {
		filter->u.ipv4.flags |= FILTER_FIELD_5TUP_DST_PT;
		filter->u.ipv4.dst_port = dport;
	}
}