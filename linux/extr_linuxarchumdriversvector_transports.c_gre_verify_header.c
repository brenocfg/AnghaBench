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
typedef  scalar_t__ uint32_t ;
struct vector_private {int /*<<< orphan*/  dev; struct uml_gre_data* transport_data; } ;
struct uml_gre_data {int key_offset; scalar_t__ rx_key; scalar_t__ key; int /*<<< orphan*/  expected_header; int /*<<< orphan*/  ipv6; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int gre_verify_header(
	uint8_t *header, struct sk_buff *skb, struct vector_private *vp)
{

	uint32_t key;
	struct uml_gre_data *td = vp->transport_data;

	if (!td->ipv6)
		header += sizeof(struct iphdr) /* fix for ipv4 raw */;

	if (*((uint32_t *) header) != *((uint32_t *) &td->expected_header)) {
		if (net_ratelimit())
			netdev_err(vp->dev, "header type disagreement, expecting %0x, got %0x",
				*((uint32_t *) &td->expected_header),
				*((uint32_t *) header)
			);
		return -1;
	}

	if (td->key) {
		key = (*(uint32_t *)(header + td->key_offset));
		if (key != td->rx_key) {
			if (net_ratelimit())
				netdev_err(vp->dev, "unknown key id %0x, expecting %0x",
						key, td->rx_key);
			return -1;
		}
	}
	return 0;
}