#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hnae3_handle {TYPE_1__* pdev; } ;
struct TYPE_4__ {int ipv4_tcp_en; int ipv4_udp_en; int ipv6_tcp_en; int ipv6_udp_en; int ipv4_sctp_en; int ipv6_sctp_en; } ;
struct hclgevf_rss_cfg {TYPE_2__ rss_tuple_sets; } ;
struct hclgevf_dev {struct hclgevf_rss_cfg rss_cfg; } ;
struct ethtool_rxnfc {int flow_type; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int HCLGEVF_D_IP_BIT ; 
 int HCLGEVF_D_PORT_BIT ; 
 int HCLGEVF_S_IP_BIT ; 
 int HCLGEVF_S_PORT_BIT ; 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 int /*<<< orphan*/  RXH_IP_DST ; 
 int /*<<< orphan*/  RXH_IP_SRC ; 
 int /*<<< orphan*/  RXH_L4_B_0_1 ; 
 int /*<<< orphan*/  RXH_L4_B_2_3 ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static int hclgevf_get_rss_tuple(struct hnae3_handle *handle,
				 struct ethtool_rxnfc *nfc)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	u8 tuple_sets;

	if (handle->pdev->revision == 0x20)
		return -EOPNOTSUPP;

	nfc->data = 0;

	switch (nfc->flow_type) {
	case TCP_V4_FLOW:
		tuple_sets = rss_cfg->rss_tuple_sets.ipv4_tcp_en;
		break;
	case UDP_V4_FLOW:
		tuple_sets = rss_cfg->rss_tuple_sets.ipv4_udp_en;
		break;
	case TCP_V6_FLOW:
		tuple_sets = rss_cfg->rss_tuple_sets.ipv6_tcp_en;
		break;
	case UDP_V6_FLOW:
		tuple_sets = rss_cfg->rss_tuple_sets.ipv6_udp_en;
		break;
	case SCTP_V4_FLOW:
		tuple_sets = rss_cfg->rss_tuple_sets.ipv4_sctp_en;
		break;
	case SCTP_V6_FLOW:
		tuple_sets = rss_cfg->rss_tuple_sets.ipv6_sctp_en;
		break;
	case IPV4_FLOW:
	case IPV6_FLOW:
		tuple_sets = HCLGEVF_S_IP_BIT | HCLGEVF_D_IP_BIT;
		break;
	default:
		return -EINVAL;
	}

	if (!tuple_sets)
		return 0;

	if (tuple_sets & HCLGEVF_D_PORT_BIT)
		nfc->data |= RXH_L4_B_2_3;
	if (tuple_sets & HCLGEVF_S_PORT_BIT)
		nfc->data |= RXH_L4_B_0_1;
	if (tuple_sets & HCLGEVF_D_IP_BIT)
		nfc->data |= RXH_IP_DST;
	if (tuple_sets & HCLGEVF_S_IP_BIT)
		nfc->data |= RXH_IP_SRC;

	return 0;
}