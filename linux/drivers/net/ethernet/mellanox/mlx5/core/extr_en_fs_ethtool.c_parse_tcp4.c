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
struct ethtool_tcpip4_spec {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_4__ {struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_3__ {struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {TYPE_2__ h_u; TYPE_1__ m_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_ip4 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tcp (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_tcp4(void *headers_c, void *headers_v, struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_tcpip4_spec *l4_mask = &fs->m_u.tcp_ip4_spec;
	struct ethtool_tcpip4_spec *l4_val  = &fs->h_u.tcp_ip4_spec;

	set_ip4(headers_c, headers_v, l4_mask->ip4src, l4_val->ip4src,
		l4_mask->ip4dst, l4_val->ip4dst);

	set_tcp(headers_c, headers_v, l4_mask->psrc, l4_val->psrc,
		l4_mask->pdst, l4_val->pdst);
}