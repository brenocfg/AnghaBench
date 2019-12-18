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
struct ethtool_tcpip4_spec {scalar_t__ pdst; scalar_t__ psrc; scalar_t__ ip4dst; scalar_t__ ip4src; scalar_t__ tos; } ;
struct TYPE_2__ {struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {TYPE_1__ m_u; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int validate_tcpudp4(struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_tcpip4_spec *l4_mask = &fs->m_u.tcp_ip4_spec;
	int ntuples = 0;

	if (l4_mask->tos)
		return -EINVAL;

	if (l4_mask->ip4src)
		ntuples++;
	if (l4_mask->ip4dst)
		ntuples++;
	if (l4_mask->psrc)
		ntuples++;
	if (l4_mask->pdst)
		ntuples++;
	/* Flow is TCP/UDP */
	return ++ntuples;
}