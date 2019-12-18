#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_9__ {int /*<<< orphan*/  packet_length; } ;
struct TYPE_8__ {int /*<<< orphan*/  placement_offset; } ;
struct qed_ll2_comp_rx_data {int /*<<< orphan*/  opaque_data_1; int /*<<< orphan*/  opaque_data_0; scalar_t__ vlan; TYPE_3__ length; TYPE_2__ u; int /*<<< orphan*/  parse_flags; scalar_t__ rx_buf_addr; struct qed_ll2_buffer* cookie; } ;
struct qed_ll2_buffer {int /*<<< orphan*/  phys_addr; int /*<<< orphan*/ * data; } ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct qed_dev {int dp_module; TYPE_5__* ll2; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {int /*<<< orphan*/  h_proto; } ;
struct TYPE_11__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  cb_cookie; TYPE_4__* cbs; int /*<<< orphan*/  rx_size; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* rx_cb ) (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,...) ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int NETIF_MSG_PKTDATA ; 
 int NETIF_MSG_RX_STATUS ; 
 scalar_t__ NET_SKB_PAD ; 
 int QED_MSG_LL2 ; 
 int QED_MSG_STORAGE ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* build_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qed_ll2_alloc_buffer (struct qed_dev*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_ll2_dealloc_buffer (struct qed_dev*,struct qed_ll2_buffer*) ; 
 int qed_ll2_post_rx_buffer (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_ll2_buffer*,int) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_ll2b_complete_rx_packet(void *cxt,
					struct qed_ll2_comp_rx_data *data)
{
	struct qed_hwfn *p_hwfn = cxt;
	struct qed_ll2_buffer *buffer = data->cookie;
	struct qed_dev *cdev = p_hwfn->cdev;
	dma_addr_t new_phys_addr;
	struct sk_buff *skb;
	bool reuse = false;
	int rc = -EINVAL;
	u8 *new_data;

	DP_VERBOSE(p_hwfn,
		   (NETIF_MSG_RX_STATUS | QED_MSG_STORAGE | NETIF_MSG_PKTDATA),
		   "Got an LL2 Rx completion: [Buffer at phys 0x%llx, offset 0x%02x] Length 0x%04x Parse_flags 0x%04x vlan 0x%04x Opaque data [0x%08x:0x%08x]\n",
		   (u64)data->rx_buf_addr,
		   data->u.placement_offset,
		   data->length.packet_length,
		   data->parse_flags,
		   data->vlan, data->opaque_data_0, data->opaque_data_1);

	if ((cdev->dp_module & NETIF_MSG_PKTDATA) && buffer->data) {
		print_hex_dump(KERN_INFO, "",
			       DUMP_PREFIX_OFFSET, 16, 1,
			       buffer->data, data->length.packet_length, false);
	}

	/* Determine if data is valid */
	if (data->length.packet_length < ETH_HLEN)
		reuse = true;

	/* Allocate a replacement for buffer; Reuse upon failure */
	if (!reuse)
		rc = qed_ll2_alloc_buffer(p_hwfn->cdev, &new_data,
					  &new_phys_addr);

	/* If need to reuse or there's no replacement buffer, repost this */
	if (rc)
		goto out_post;
	dma_unmap_single(&cdev->pdev->dev, buffer->phys_addr,
			 cdev->ll2->rx_size, DMA_FROM_DEVICE);

	skb = build_skb(buffer->data, 0);
	if (!skb) {
		DP_INFO(cdev, "Failed to build SKB\n");
		kfree(buffer->data);
		goto out_post1;
	}

	data->u.placement_offset += NET_SKB_PAD;
	skb_reserve(skb, data->u.placement_offset);
	skb_put(skb, data->length.packet_length);
	skb_checksum_none_assert(skb);

	/* Get parital ethernet information instead of eth_type_trans(),
	 * Since we don't have an associated net_device.
	 */
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	/* Pass SKB onward */
	if (cdev->ll2->cbs && cdev->ll2->cbs->rx_cb) {
		if (data->vlan)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       data->vlan);
		cdev->ll2->cbs->rx_cb(cdev->ll2->cb_cookie, skb,
				      data->opaque_data_0,
				      data->opaque_data_1);
	} else {
		DP_VERBOSE(p_hwfn, (NETIF_MSG_RX_STATUS | NETIF_MSG_PKTDATA |
				    QED_MSG_LL2 | QED_MSG_STORAGE),
			   "Dropping the packet\n");
		kfree(buffer->data);
	}

out_post1:
	/* Update Buffer information and update FW producer */
	buffer->data = new_data;
	buffer->phys_addr = new_phys_addr;

out_post:
	rc = qed_ll2_post_rx_buffer(p_hwfn, cdev->ll2->handle,
				    buffer->phys_addr, 0, buffer, 1);
	if (rc)
		qed_ll2_dealloc_buffer(cdev, buffer);
}