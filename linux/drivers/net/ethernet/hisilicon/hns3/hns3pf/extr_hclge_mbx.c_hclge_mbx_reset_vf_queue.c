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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_vport {int dummy; } ;
struct hclge_mbx_vf_to_pf_cmd {int /*<<< orphan*/ * msg; } ;
typedef  int /*<<< orphan*/  queue_id ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_reset_vf_queue (struct hclge_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hclge_mbx_reset_vf_queue(struct hclge_vport *vport,
				     struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	u16 queue_id;

	memcpy(&queue_id, &mbx_req->msg[2], sizeof(queue_id));

	hclge_reset_vf_queue(vport, queue_id);

	/* send response msg to VF after queue reset complete */
	hclge_gen_resp_to_vf(vport, mbx_req, 0, NULL, 0);
}