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
struct hclge_rss_input_tuple_cmd {int /*<<< orphan*/  ipv6_fragment_en; int /*<<< orphan*/  ipv6_sctp_en; int /*<<< orphan*/  ipv6_udp_en; int /*<<< orphan*/  ipv6_tcp_en; int /*<<< orphan*/  ipv4_fragment_en; int /*<<< orphan*/  ipv4_sctp_en; int /*<<< orphan*/  ipv4_udp_en; int /*<<< orphan*/  ipv4_tcp_en; } ;
struct hclge_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; TYPE_3__* vport; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipv6_fragment_en; int /*<<< orphan*/  ipv6_sctp_en; int /*<<< orphan*/  ipv6_udp_en; int /*<<< orphan*/  ipv6_tcp_en; int /*<<< orphan*/  ipv4_fragment_en; int /*<<< orphan*/  ipv4_sctp_en; int /*<<< orphan*/  ipv4_udp_en; int /*<<< orphan*/  ipv4_tcp_en; } ;
struct TYPE_6__ {TYPE_1__ rss_tuple_sets; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_RSS_INPUT_TUPLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_get_rss_type (TYPE_3__*) ; 

__attribute__((used)) static int hclge_set_rss_input_tuple(struct hclge_dev *hdev)
{
	struct hclge_rss_input_tuple_cmd *req;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RSS_INPUT_TUPLE, false);

	req = (struct hclge_rss_input_tuple_cmd *)desc.data;

	/* Get the tuple cfg from pf */
	req->ipv4_tcp_en = hdev->vport[0].rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = hdev->vport[0].rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = hdev->vport[0].rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = hdev->vport[0].rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = hdev->vport[0].rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = hdev->vport[0].rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = hdev->vport[0].rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = hdev->vport[0].rss_tuple_sets.ipv6_fragment_en;
	hclge_get_rss_type(&hdev->vport[0]);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Configure rss input fail, status = %d\n", ret);
	return ret;
}