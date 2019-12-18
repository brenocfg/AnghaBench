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
struct hclgevf_rss_input_tuple_cmd {int /*<<< orphan*/  ipv6_fragment_en; int /*<<< orphan*/  ipv6_sctp_en; int /*<<< orphan*/  ipv6_udp_en; int /*<<< orphan*/  ipv6_tcp_en; int /*<<< orphan*/  ipv4_fragment_en; int /*<<< orphan*/  ipv4_sctp_en; int /*<<< orphan*/  ipv4_udp_en; int /*<<< orphan*/  ipv4_tcp_en; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipv6_fragment_en; int /*<<< orphan*/  ipv6_sctp_en; int /*<<< orphan*/  ipv6_udp_en; int /*<<< orphan*/  ipv6_tcp_en; int /*<<< orphan*/  ipv4_fragment_en; int /*<<< orphan*/  ipv4_sctp_en; int /*<<< orphan*/  ipv4_udp_en; int /*<<< orphan*/  ipv4_tcp_en; } ;
struct hclgevf_rss_cfg {TYPE_1__ rss_tuple_sets; } ;
struct hclgevf_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_OPC_RSS_INPUT_TUPLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclgevf_set_rss_input_tuple(struct hclgevf_dev *hdev,
				       struct hclgevf_rss_cfg *rss_cfg)
{
	struct hclgevf_rss_input_tuple_cmd *req;
	struct hclgevf_desc desc;
	int ret;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_INPUT_TUPLE, false);

	req = (struct hclgevf_rss_input_tuple_cmd *)desc.data;

	req->ipv4_tcp_en = rss_cfg->rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = rss_cfg->rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = rss_cfg->rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = rss_cfg->rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = rss_cfg->rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = rss_cfg->rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = rss_cfg->rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = rss_cfg->rss_tuple_sets.ipv6_fragment_en;

	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Configure rss input fail, status = %d\n", ret);
	return ret;
}