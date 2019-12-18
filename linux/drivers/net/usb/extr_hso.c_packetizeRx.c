#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct iphdr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  tot_len; } ;
struct hso_net {int rx_parse_state; unsigned int rx_buf_missing; int rx_buf_size; TYPE_7__* net; TYPE_3__* skb_rx_buf; TYPE_1__ rx_ip_hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_11__ {TYPE_2__ stats; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 unsigned short DEFAULT_MRU ; 
 int /*<<< orphan*/  DUMP (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_IP ; 
#define  WAIT_DATA 130 
#define  WAIT_IP 129 
#define  WAIT_SYNC 128 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned short) ; 
 int /*<<< orphan*/  hso_dbg (int,char*,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned short) ; 
 int /*<<< orphan*/  min (int,int) ; 
 TYPE_3__* netdev_alloc_skb (TYPE_7__*,unsigned short) ; 
 int /*<<< orphan*/  netif_rx (TYPE_3__*) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (TYPE_3__*,...) ; 
 int /*<<< orphan*/  skb_reset_mac_header (TYPE_3__*) ; 

__attribute__((used)) static void packetizeRx(struct hso_net *odev, unsigned char *ip_pkt,
			unsigned int count, unsigned char is_eop)
{
	unsigned short temp_bytes;
	unsigned short buffer_offset = 0;
	unsigned short frame_len;

	/* log if needed */
	hso_dbg(0x1, "Rx %d bytes\n", count);
	DUMP(ip_pkt, min(128, (int)count));

	while (count) {
		switch (odev->rx_parse_state) {
		case WAIT_IP:
			/* waiting for IP header. */
			/* wanted bytes - size of ip header */
			temp_bytes =
			    (count <
			     odev->rx_buf_missing) ? count : odev->
			    rx_buf_missing;

			memcpy(((unsigned char *)(&odev->rx_ip_hdr)) +
			       odev->rx_buf_size, ip_pkt + buffer_offset,
			       temp_bytes);

			odev->rx_buf_size += temp_bytes;
			buffer_offset += temp_bytes;
			odev->rx_buf_missing -= temp_bytes;
			count -= temp_bytes;

			if (!odev->rx_buf_missing) {
				/* header is complete allocate an sk_buffer and
				 * continue to WAIT_DATA */
				frame_len = ntohs(odev->rx_ip_hdr.tot_len);

				if ((frame_len > DEFAULT_MRU) ||
				    (frame_len < sizeof(struct iphdr))) {
					dev_err(&odev->net->dev,
						"Invalid frame (%d) length\n",
						frame_len);
					odev->rx_parse_state = WAIT_SYNC;
					continue;
				}
				/* Allocate an sk_buff */
				odev->skb_rx_buf = netdev_alloc_skb(odev->net,
								    frame_len);
				if (!odev->skb_rx_buf) {
					/* We got no receive buffer. */
					hso_dbg(0x1, "could not allocate memory\n");
					odev->rx_parse_state = WAIT_SYNC;
					continue;
				}

				/* Copy what we got so far. make room for iphdr
				 * after tail. */
				skb_put_data(odev->skb_rx_buf,
					     (char *)&(odev->rx_ip_hdr),
					     sizeof(struct iphdr));

				/* ETH_HLEN */
				odev->rx_buf_size = sizeof(struct iphdr);

				/* Filip actually use .tot_len */
				odev->rx_buf_missing =
				    frame_len - sizeof(struct iphdr);
				odev->rx_parse_state = WAIT_DATA;
			}
			break;

		case WAIT_DATA:
			temp_bytes = (count < odev->rx_buf_missing)
					? count : odev->rx_buf_missing;

			/* Copy the rest of the bytes that are left in the
			 * buffer into the waiting sk_buf. */
			/* Make room for temp_bytes after tail. */
			skb_put_data(odev->skb_rx_buf,
				     ip_pkt + buffer_offset,
				     temp_bytes);

			odev->rx_buf_missing -= temp_bytes;
			count -= temp_bytes;
			buffer_offset += temp_bytes;
			odev->rx_buf_size += temp_bytes;
			if (!odev->rx_buf_missing) {
				/* Packet is complete. Inject into stack. */
				/* We have IP packet here */
				odev->skb_rx_buf->protocol = cpu_to_be16(ETH_P_IP);
				skb_reset_mac_header(odev->skb_rx_buf);

				/* Ship it off to the kernel */
				netif_rx(odev->skb_rx_buf);
				/* No longer our buffer. */
				odev->skb_rx_buf = NULL;

				/* update out statistics */
				odev->net->stats.rx_packets++;

				odev->net->stats.rx_bytes += odev->rx_buf_size;

				odev->rx_buf_size = 0;
				odev->rx_buf_missing = sizeof(struct iphdr);
				odev->rx_parse_state = WAIT_IP;
			}
			break;

		case WAIT_SYNC:
			hso_dbg(0x1, " W_S\n");
			count = 0;
			break;
		default:
			hso_dbg(0x1, "\n");
			count--;
			break;
		}
	}

	/* Recovery mechanism for WAIT_SYNC state. */
	if (is_eop) {
		if (odev->rx_parse_state == WAIT_SYNC) {
			odev->rx_parse_state = WAIT_IP;
			odev->rx_buf_size = 0;
			odev->rx_buf_missing = sizeof(struct iphdr);
		}
	}
}