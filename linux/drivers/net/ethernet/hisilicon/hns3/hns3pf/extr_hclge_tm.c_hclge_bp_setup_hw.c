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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct hclge_vport {int qs_offset; } ;
struct hclge_dev {int num_alloc_vport; struct hclge_vport* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_BP_GRP_ID_M ; 
 int /*<<< orphan*/  HCLGE_BP_GRP_ID_S ; 
 int HCLGE_BP_GRP_NUM ; 
 int /*<<< orphan*/  HCLGE_BP_SUB_GRP_ID_M ; 
 int /*<<< orphan*/  HCLGE_BP_SUB_GRP_ID_S ; 
 int hclge_tm_qs_bp_cfg (struct hclge_dev*,int,int,int) ; 
 int hnae3_get_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_bp_setup_hw(struct hclge_dev *hdev, u8 tc)
{
	int i;

	for (i = 0; i < HCLGE_BP_GRP_NUM; i++) {
		u32 qs_bitmap = 0;
		int k, ret;

		for (k = 0; k < hdev->num_alloc_vport; k++) {
			struct hclge_vport *vport = &hdev->vport[k];
			u16 qs_id = vport->qs_offset + tc;
			u8 grp, sub_grp;

			grp = hnae3_get_field(qs_id, HCLGE_BP_GRP_ID_M,
					      HCLGE_BP_GRP_ID_S);
			sub_grp = hnae3_get_field(qs_id, HCLGE_BP_SUB_GRP_ID_M,
						  HCLGE_BP_SUB_GRP_ID_S);
			if (i == grp)
				qs_bitmap |= (1 << sub_grp);
		}

		ret = hclge_tm_qs_bp_cfg(hdev, tc, i, qs_bitmap);
		if (ret)
			return ret;
	}

	return 0;
}