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
typedef  int u32 ;
struct usbnet {TYPE_1__* net; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct gl_packet {int /*<<< orphan*/ * packet_data; int /*<<< orphan*/  packet_length; } ;
struct gl_header {struct gl_packet packets; int /*<<< orphan*/  packet_count; } ;
struct TYPE_2__ {scalar_t__ hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int GL_MAX_PACKET_LEN ; 
 int GL_MAX_TRANSMIT_PACKETS ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbnet_skb_return (struct usbnet*,struct sk_buff*) ; 

__attribute__((used)) static int genelink_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	struct gl_header	*header;
	struct gl_packet	*packet;
	struct sk_buff		*gl_skb;
	u32			size;
	u32			count;

	/* This check is no longer done by usbnet */
	if (skb->len < dev->net->hard_header_len)
		return 0;

	header = (struct gl_header *) skb->data;

	// get the packet count of the received skb
	count = le32_to_cpu(header->packet_count);
	if (count > GL_MAX_TRANSMIT_PACKETS) {
		netdev_dbg(dev->net,
			   "genelink: invalid received packet count %u\n",
			   count);
		return 0;
	}

	// set the current packet pointer to the first packet
	packet = &header->packets;

	// decrement the length for the packet count size 4 bytes
	skb_pull(skb, 4);

	while (count > 1) {
		// get the packet length
		size = le32_to_cpu(packet->packet_length);

		// this may be a broken packet
		if (size > GL_MAX_PACKET_LEN) {
			netdev_dbg(dev->net, "genelink: invalid rx length %d\n",
				   size);
			return 0;
		}

		// allocate the skb for the individual packet
		gl_skb = alloc_skb(size, GFP_ATOMIC);
		if (gl_skb) {

			// copy the packet data to the new skb
			skb_put_data(gl_skb, packet->packet_data, size);
			usbnet_skb_return(dev, gl_skb);
		}

		// advance to the next packet
		packet = (struct gl_packet *)&packet->packet_data[size];
		count--;

		// shift the data pointer to the next gl_packet
		skb_pull(skb, size + 4);
	}

	// skip the packet length field 4 bytes
	skb_pull(skb, 4);

	if (skb->len > GL_MAX_PACKET_LEN) {
		netdev_dbg(dev->net, "genelink: invalid rx length %d\n",
			   skb->len);
		return 0;
	}
	return 1;
}