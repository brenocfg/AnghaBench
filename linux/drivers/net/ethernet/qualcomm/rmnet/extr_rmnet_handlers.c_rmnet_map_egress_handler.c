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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct rmnet_port {int data_format; } ;
struct rmnet_map_ul_csum_header {int dummy; } ;
struct rmnet_map_header {int /*<<< orphan*/  mux_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_MAP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int RMNET_FLAGS_EGRESS_MAP_CKSUMV4 ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rmnet_map_header* rmnet_map_add_map_header (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmnet_map_checksum_uplink_packet (struct sk_buff*,struct net_device*) ; 
 int skb_headroom (struct sk_buff*) ; 

__attribute__((used)) static int rmnet_map_egress_handler(struct sk_buff *skb,
				    struct rmnet_port *port, u8 mux_id,
				    struct net_device *orig_dev)
{
	int required_headroom, additional_header_len;
	struct rmnet_map_header *map_header;

	additional_header_len = 0;
	required_headroom = sizeof(struct rmnet_map_header);

	if (port->data_format & RMNET_FLAGS_EGRESS_MAP_CKSUMV4) {
		additional_header_len = sizeof(struct rmnet_map_ul_csum_header);
		required_headroom += additional_header_len;
	}

	if (skb_headroom(skb) < required_headroom) {
		if (pskb_expand_head(skb, required_headroom, 0, GFP_ATOMIC))
			return -ENOMEM;
	}

	if (port->data_format & RMNET_FLAGS_EGRESS_MAP_CKSUMV4)
		rmnet_map_checksum_uplink_packet(skb, orig_dev);

	map_header = rmnet_map_add_map_header(skb, additional_header_len, 0);
	if (!map_header)
		return -ENOMEM;

	map_header->mux_id = mux_id;

	skb->protocol = htons(ETH_P_MAP);

	return 0;
}