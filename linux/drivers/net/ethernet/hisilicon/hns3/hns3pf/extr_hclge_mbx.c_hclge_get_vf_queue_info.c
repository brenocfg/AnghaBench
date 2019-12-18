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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rss_size; } ;
struct TYPE_4__ {TYPE_1__ kinfo; } ;
struct hclge_vport {TYPE_2__ nic; int /*<<< orphan*/  alloc_tqps; struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int dummy; } ;
struct hclge_dev {int /*<<< orphan*/  rx_buf_len; } ;

/* Variables and functions */
 int HCLGE_TQPS_RSS_INFO_LEN ; 
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_vf_queue_info(struct hclge_vport *vport,
				   struct hclge_mbx_vf_to_pf_cmd *mbx_req,
				   bool gen_resp)
{
#define HCLGE_TQPS_RSS_INFO_LEN		6
	u8 resp_data[HCLGE_TQPS_RSS_INFO_LEN];
	struct hclge_dev *hdev = vport->back;

	/* get the queue related info */
	memcpy(&resp_data[0], &vport->alloc_tqps, sizeof(u16));
	memcpy(&resp_data[2], &vport->nic.kinfo.rss_size, sizeof(u16));
	memcpy(&resp_data[4], &hdev->rx_buf_len, sizeof(u16));

	return hclge_gen_resp_to_vf(vport, mbx_req, 0, resp_data,
				    HCLGE_TQPS_RSS_INFO_LEN);
}