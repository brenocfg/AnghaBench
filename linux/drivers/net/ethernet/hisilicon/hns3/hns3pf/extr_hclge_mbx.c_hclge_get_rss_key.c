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
typedef  int u8 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; } ;
struct hclge_dev {TYPE_1__* vport; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rss_hash_key; } ;

/* Variables and functions */
 int HCLGE_RSS_MBX_RESP_LEN ; 
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_rss_key(struct hclge_vport *vport,
			     struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
#define HCLGE_RSS_MBX_RESP_LEN	8
	u8 resp_data[HCLGE_RSS_MBX_RESP_LEN];
	struct hclge_dev *hdev = vport->back;
	u8 index;

	index = mbx_req->msg[2];

	memcpy(&resp_data[0],
	       &hdev->vport[0].rss_hash_key[index * HCLGE_RSS_MBX_RESP_LEN],
	       HCLGE_RSS_MBX_RESP_LEN);

	return hclge_gen_resp_to_vf(vport, mbx_req, 0, resp_data,
				    HCLGE_RSS_MBX_RESP_LEN);
}