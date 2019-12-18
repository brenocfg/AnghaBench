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
struct hclge_vport {int /*<<< orphan*/  nic; } ;
struct hclge_mbx_vf_to_pf_cmd {int /*<<< orphan*/ * msg; } ;
typedef  int /*<<< orphan*/  queue_id ;
typedef  int /*<<< orphan*/  qid_in_pf ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_covert_handle_qid_global (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_queue_id_in_pf(struct hclge_vport *vport,
				    struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	u16 queue_id, qid_in_pf;
	u8 resp_data[2];

	memcpy(&queue_id, &mbx_req->msg[2], sizeof(queue_id));
	qid_in_pf = hclge_covert_handle_qid_global(&vport->nic, queue_id);
	memcpy(resp_data, &qid_in_pf, sizeof(qid_in_pf));

	return hclge_gen_resp_to_vf(vport, mbx_req, 0, resp_data, 2);
}