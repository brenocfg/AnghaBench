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
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  module_type; int /*<<< orphan*/  media_type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  resp_data ;

/* Variables and functions */
 int hclge_gen_resp_to_vf (struct hclge_vport*,struct hclge_mbx_vf_to_pf_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclge_get_vf_media_type(struct hclge_vport *vport,
				   struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	struct hclge_dev *hdev = vport->back;
	u8 resp_data[2];

	resp_data[0] = hdev->hw.mac.media_type;
	resp_data[1] = hdev->hw.mac.module_type;
	return hclge_gen_resp_to_vf(vport, mbx_req, 0, resp_data,
				    sizeof(resp_data));
}