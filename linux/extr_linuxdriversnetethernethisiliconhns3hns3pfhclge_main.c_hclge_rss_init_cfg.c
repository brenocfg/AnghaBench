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
struct TYPE_2__ {void* ipv6_fragment_en; void* ipv6_sctp_en; void* ipv6_udp_en; void* ipv6_tcp_en; void* ipv4_fragment_en; void* ipv4_sctp_en; void* ipv4_udp_en; void* ipv4_tcp_en; } ;
struct hclge_vport {int /*<<< orphan*/  rss_hash_key; int /*<<< orphan*/  rss_algo; TYPE_1__ rss_tuple_sets; } ;
struct hclge_dev {int num_vmdq_vport; struct hclge_vport* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_RSS_HASH_ALGO_TOEPLITZ ; 
 void* HCLGE_RSS_INPUT_TUPLE_OTHER ; 
 void* HCLGE_RSS_INPUT_TUPLE_SCTP ; 
 int /*<<< orphan*/  HCLGE_RSS_KEY_SIZE ; 
 int /*<<< orphan*/  hclge_rss_indir_init_cfg (struct hclge_dev*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_rss_init_cfg(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	int i;

	for (i = 0; i < hdev->num_vmdq_vport + 1; i++) {
		vport[i].rss_tuple_sets.ipv4_tcp_en =
			HCLGE_RSS_INPUT_TUPLE_OTHER;
		vport[i].rss_tuple_sets.ipv4_udp_en =
			HCLGE_RSS_INPUT_TUPLE_OTHER;
		vport[i].rss_tuple_sets.ipv4_sctp_en =
			HCLGE_RSS_INPUT_TUPLE_SCTP;
		vport[i].rss_tuple_sets.ipv4_fragment_en =
			HCLGE_RSS_INPUT_TUPLE_OTHER;
		vport[i].rss_tuple_sets.ipv6_tcp_en =
			HCLGE_RSS_INPUT_TUPLE_OTHER;
		vport[i].rss_tuple_sets.ipv6_udp_en =
			HCLGE_RSS_INPUT_TUPLE_OTHER;
		vport[i].rss_tuple_sets.ipv6_sctp_en =
			HCLGE_RSS_INPUT_TUPLE_SCTP;
		vport[i].rss_tuple_sets.ipv6_fragment_en =
			HCLGE_RSS_INPUT_TUPLE_OTHER;

		vport[i].rss_algo = HCLGE_RSS_HASH_ALGO_TOEPLITZ;

		netdev_rss_key_fill(vport[i].rss_hash_key, HCLGE_RSS_KEY_SIZE);
	}

	hclge_rss_indir_init_cfg(hdev);
}