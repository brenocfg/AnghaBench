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
typedef  int uint32_t ;
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
typedef  enum hubp_ind_block_size { ____Placeholder_hubp_ind_block_size } hubp_ind_block_size ;

/* Variables and functions */
 int /*<<< orphan*/  DCSURF_SURFACE_CONTROL ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_DCC_EN ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_DCC_IND_64B_BLK ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SECONDARY_SURFACE_DCC_EN ; 
 int /*<<< orphan*/  SECONDARY_SURFACE_DCC_IND_64B_BLK ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 

void hubp2_dcc_control(struct hubp *hubp, bool enable,
		enum hubp_ind_block_size independent_64b_blks)
{
	uint32_t dcc_en = enable ? 1 : 0;
	uint32_t dcc_ind_64b_blk = independent_64b_blks ? 1 : 0;
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
			PRIMARY_SURFACE_DCC_EN, dcc_en,
			PRIMARY_SURFACE_DCC_IND_64B_BLK, dcc_ind_64b_blk,
			SECONDARY_SURFACE_DCC_EN, dcc_en,
			SECONDARY_SURFACE_DCC_IND_64B_BLK, dcc_ind_64b_blk);
}