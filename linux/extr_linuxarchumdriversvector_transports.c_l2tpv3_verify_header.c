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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vector_private {int /*<<< orphan*/  dev; struct uml_l2tpv3_data* transport_data; } ;
struct uml_l2tpv3_data {int cookie_offset; scalar_t__ rx_cookie; int session_offset; scalar_t__ rx_session; scalar_t__ cookie_is_64; scalar_t__ cookie; int /*<<< orphan*/  ipv6; int /*<<< orphan*/  udp; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int l2tpv3_verify_header(
	uint8_t *header, struct sk_buff *skb, struct vector_private *vp)
{
	struct uml_l2tpv3_data *td = vp->transport_data;
	uint32_t *session;
	uint64_t cookie;

	if ((!td->udp) && (!td->ipv6))
		header += sizeof(struct iphdr) /* fix for ipv4 raw */;

	/* we do not do a strict check for "data" packets as per
	 * the RFC spec because the pure IP spec does not have
	 * that anyway.
	 */

	if (td->cookie) {
		if (td->cookie_is_64)
			cookie = *(uint64_t *)(header + td->cookie_offset);
		else
			cookie = *(uint32_t *)(header + td->cookie_offset);
		if (cookie != td->rx_cookie) {
			if (net_ratelimit())
				netdev_err(vp->dev, "uml_l2tpv3: unknown cookie id");
			return -1;
		}
	}
	session = (uint32_t *) (header + td->session_offset);
	if (*session != td->rx_session) {
		if (net_ratelimit())
			netdev_err(vp->dev, "uml_l2tpv3: session mismatch");
		return -1;
	}
	return 0;
}