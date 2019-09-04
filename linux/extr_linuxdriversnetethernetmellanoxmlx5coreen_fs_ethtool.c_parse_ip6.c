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
struct ethtool_usrip6_spec {scalar_t__ l4_proto; int /*<<< orphan*/  ip6dst; int /*<<< orphan*/  ip6src; } ;
struct TYPE_4__ {struct ethtool_usrip6_spec usr_ip6_spec; } ;
struct TYPE_3__ {struct ethtool_usrip6_spec usr_ip6_spec; } ;
struct ethtool_rx_flow_spec {TYPE_2__ h_u; TYPE_1__ m_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_FTE_SET (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ip_protocol ; 
 int /*<<< orphan*/  set_ip6 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_ip6(void *headers_c, void *headers_v, struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_usrip6_spec *l3_mask = &fs->m_u.usr_ip6_spec;
	struct ethtool_usrip6_spec *l3_val  = &fs->h_u.usr_ip6_spec;

	set_ip6(headers_c, headers_v, l3_mask->ip6src,
		l3_val->ip6src, l3_mask->ip6dst, l3_val->ip6dst);

	if (l3_mask->l4_proto) {
		MLX5E_FTE_SET(headers_c, ip_protocol, l3_mask->l4_proto);
		MLX5E_FTE_SET(headers_v, ip_protocol, l3_val->l4_proto);
	}
}