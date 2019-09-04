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
struct be_rx_compl_info {int /*<<< orphan*/  err; scalar_t__ ipv6; scalar_t__ ip_csum; scalar_t__ l4_csum; scalar_t__ udpf; scalar_t__ tcpf; } ;

/* Variables and functions */

__attribute__((used)) static inline bool csum_passed(struct be_rx_compl_info *rxcp)
{
	/* L4 checksum is not reliable for non TCP/UDP packets.
	 * Also ignore ipcksm for ipv6 pkts
	 */
	return (rxcp->tcpf || rxcp->udpf) && rxcp->l4_csum &&
		(rxcp->ip_csum || rxcp->ipv6) && !rxcp->err;
}