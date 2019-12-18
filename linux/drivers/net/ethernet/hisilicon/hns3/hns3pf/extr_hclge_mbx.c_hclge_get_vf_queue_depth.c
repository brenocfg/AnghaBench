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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int dummy; } ;
struct hclge_dev {int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; } ;

/* Variables and functions */
 int HCLGE_TQPS_DEPTH_INFO_LEN ; 
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_vf_queue_depth(struct hclge_vport *vport,
				    struct hclge_mbx_vf_to_pf_cmd *mbx_req,
				    bool gen_resp)
{
#define HCLGE_TQPS_DEPTH_INFO_LEN	4
	u8 resp_data[HCLGE_TQPS_DEPTH_INFO_LEN];
	struct hclge_dev *hdev = vport->back;

	/* get the queue depth info */
	memcpy(&resp_data[0], &hdev->num_tx_desc, sizeof(u16));
	memcpy(&resp_data[2], &hdev->num_rx_desc, sizeof(u16));
	return hclge_gen_resp_to_vf(vport, mbx_req, 0, resp_data,
				    HCLGE_TQPS_DEPTH_INFO_LEN);
}