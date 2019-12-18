#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct hnae3_handle {TYPE_1__* pdev; } ;
struct hclgevf_rss_input_tuple_cmd {void* ipv6_fragment_en; void* ipv6_sctp_en; void* ipv6_udp_en; void* ipv6_tcp_en; void* ipv4_fragment_en; void* ipv4_sctp_en; void* ipv4_udp_en; void* ipv4_tcp_en; } ;
struct TYPE_6__ {void* ipv6_fragment_en; void* ipv6_sctp_en; void* ipv6_udp_en; void* ipv6_tcp_en; void* ipv4_fragment_en; void* ipv4_sctp_en; void* ipv4_udp_en; void* ipv4_tcp_en; } ;
struct hclgevf_rss_cfg {TYPE_3__ rss_tuple_sets; } ;
struct hclgevf_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; struct hclgevf_rss_cfg rss_cfg; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCLGEVF_OPC_RSS_INPUT_TUPLE ; 
 void* HCLGEVF_RSS_INPUT_TUPLE_OTHER ; 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 
 void* hclgevf_get_rss_hash_bits (struct ethtool_rxnfc*) ; 

__attribute__((used)) static int hclgevf_set_rss_tuple(struct hnae3_handle *handle,
				 struct ethtool_rxnfc *nfc)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	struct hclgevf_rss_input_tuple_cmd *req;
	struct hclgevf_desc desc;
	u8 tuple_sets;
	int ret;

	if (handle->pdev->revision == 0x20)
		return -EOPNOTSUPP;

	if (nfc->data &
	    ~(RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 | RXH_L4_B_2_3))
		return -EINVAL;

	req = (struct hclgevf_rss_input_tuple_cmd *)desc.data;
	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_INPUT_TUPLE, false);

	req->ipv4_tcp_en = rss_cfg->rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = rss_cfg->rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = rss_cfg->rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = rss_cfg->rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = rss_cfg->rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = rss_cfg->rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = rss_cfg->rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = rss_cfg->rss_tuple_sets.ipv6_fragment_en;

	tuple_sets = hclgevf_get_rss_hash_bits(nfc);
	switch (nfc->flow_type) {
	case TCP_V4_FLOW:
		req->ipv4_tcp_en = tuple_sets;
		break;
	case TCP_V6_FLOW:
		req->ipv6_tcp_en = tuple_sets;
		break;
	case UDP_V4_FLOW:
		req->ipv4_udp_en = tuple_sets;
		break;
	case UDP_V6_FLOW:
		req->ipv6_udp_en = tuple_sets;
		break;
	case SCTP_V4_FLOW:
		req->ipv4_sctp_en = tuple_sets;
		break;
	case SCTP_V6_FLOW:
		if ((nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			return -EINVAL;

		req->ipv6_sctp_en = tuple_sets;
		break;
	case IPV4_FLOW:
		req->ipv4_fragment_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		break;
	case IPV6_FLOW:
		req->ipv6_fragment_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		break;
	default:
		return -EINVAL;
	}

	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Set rss tuple fail, status = %d\n", ret);
		return ret;
	}

	rss_cfg->rss_tuple_sets.ipv4_tcp_en = req->ipv4_tcp_en;
	rss_cfg->rss_tuple_sets.ipv4_udp_en = req->ipv4_udp_en;
	rss_cfg->rss_tuple_sets.ipv4_sctp_en = req->ipv4_sctp_en;
	rss_cfg->rss_tuple_sets.ipv4_fragment_en = req->ipv4_fragment_en;
	rss_cfg->rss_tuple_sets.ipv6_tcp_en = req->ipv6_tcp_en;
	rss_cfg->rss_tuple_sets.ipv6_udp_en = req->ipv6_udp_en;
	rss_cfg->rss_tuple_sets.ipv6_sctp_en = req->ipv6_sctp_en;
	rss_cfg->rss_tuple_sets.ipv6_fragment_en = req->ipv6_fragment_en;
	return 0;
}