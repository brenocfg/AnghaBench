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
union rdma_network_hdr {int /*<<< orphan*/  ibgrh; int /*<<< orphan*/  roce4grh; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ipv6hdr {int version; } ;
struct iphdr {int version; int ihl; scalar_t__ check; } ;
typedef  int /*<<< orphan*/  ip4h_checked ;

/* Variables and functions */
 scalar_t__ ip_fast_csum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct iphdr*,struct iphdr const*,int) ; 

int ib_get_rdma_header_version(const union rdma_network_hdr *hdr)
{
	const struct iphdr *ip4h = (struct iphdr *)&hdr->roce4grh;
	struct iphdr ip4h_checked;
	const struct ipv6hdr *ip6h = (struct ipv6hdr *)&hdr->ibgrh;

	/* If it's IPv6, the version must be 6, otherwise, the first
	 * 20 bytes (before the IPv4 header) are garbled.
	 */
	if (ip6h->version != 6)
		return (ip4h->version == 4) ? 4 : 0;
	/* version may be 6 or 4 because the first 20 bytes could be garbled */

	/* RoCE v2 requires no options, thus header length
	 * must be 5 words
	 */
	if (ip4h->ihl != 5)
		return 6;

	/* Verify checksum.
	 * We can't write on scattered buffers so we need to copy to
	 * temp buffer.
	 */
	memcpy(&ip4h_checked, ip4h, sizeof(ip4h_checked));
	ip4h_checked.check = 0;
	ip4h_checked.check = ip_fast_csum((u8 *)&ip4h_checked, 5);
	/* if IPv4 header checksum is OK, believe it */
	if (ip4h->check == ip4h_checked.check)
		return 4;
	return 6;
}