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
typedef  int /*<<< orphan*/  u32 ;
struct hclge_vport {int dummy; } ;
struct hclge_mbx_vf_to_pf_cmd {int /*<<< orphan*/ * msg; } ;
typedef  int /*<<< orphan*/  mtu ;

/* Variables and functions */
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclge_set_vport_mtu (struct hclge_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_set_vf_mtu(struct hclge_vport *vport,
			    struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	int ret;
	u32 mtu;

	memcpy(&mtu, &mbx_req->msg[2], sizeof(mtu));
	ret = hclge_set_vport_mtu(vport, mtu);

	return hclge_gen_resp_to_vf(vport, mbx_req, ret, NULL, 0);
}