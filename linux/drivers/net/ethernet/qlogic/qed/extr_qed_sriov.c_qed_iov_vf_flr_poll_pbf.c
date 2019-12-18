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
typedef  scalar_t__ u32 ;
struct qed_vf_info {int /*<<< orphan*/  abs_vf_id; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int MAX_NUM_VOQS_E4 ; 
 scalar_t__ PBF_REG_NUM_BLOCKS_ALLOCATED_CONS_VOQ0 ; 
 scalar_t__ PBF_REG_NUM_BLOCKS_ALLOCATED_PROD_VOQ0 ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 

__attribute__((used)) static int
qed_iov_vf_flr_poll_pbf(struct qed_hwfn *p_hwfn,
			struct qed_vf_info *p_vf, struct qed_ptt *p_ptt)
{
	u32 cons[MAX_NUM_VOQS_E4], distance[MAX_NUM_VOQS_E4];
	int i, cnt;

	/* Read initial consumers & producers */
	for (i = 0; i < MAX_NUM_VOQS_E4; i++) {
		u32 prod;

		cons[i] = qed_rd(p_hwfn, p_ptt,
				 PBF_REG_NUM_BLOCKS_ALLOCATED_CONS_VOQ0 +
				 i * 0x40);
		prod = qed_rd(p_hwfn, p_ptt,
			      PBF_REG_NUM_BLOCKS_ALLOCATED_PROD_VOQ0 +
			      i * 0x40);
		distance[i] = prod - cons[i];
	}

	/* Wait for consumers to pass the producers */
	i = 0;
	for (cnt = 0; cnt < 50; cnt++) {
		for (; i < MAX_NUM_VOQS_E4; i++) {
			u32 tmp;

			tmp = qed_rd(p_hwfn, p_ptt,
				     PBF_REG_NUM_BLOCKS_ALLOCATED_CONS_VOQ0 +
				     i * 0x40);
			if (distance[i] > tmp - cons[i])
				break;
		}

		if (i == MAX_NUM_VOQS_E4)
			break;

		msleep(20);
	}

	if (cnt == 50) {
		DP_ERR(p_hwfn, "VF[%d] - pbf polling failed on VOQ %d\n",
		       p_vf->abs_vf_id, i);
		return -EBUSY;
	}

	return 0;
}