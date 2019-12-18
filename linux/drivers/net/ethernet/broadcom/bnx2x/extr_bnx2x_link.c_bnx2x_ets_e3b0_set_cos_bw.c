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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0 ; 
 int NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1 ; 
 int NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2 ; 
 int NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3 ; 
 int NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4 ; 
 int NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5 ; 
 int NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0 ; 
 int NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1 ; 
 int NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2 ; 
 int PBF_REG_COS0_WEIGHT_P0 ; 
 int PBF_REG_COS0_WEIGHT_P1 ; 
 int PBF_REG_COS1_WEIGHT_P0 ; 
 int PBF_REG_COS1_WEIGHT_P1 ; 
 int PBF_REG_COS2_WEIGHT_P0 ; 
 int PBF_REG_COS2_WEIGHT_P1 ; 
 int PBF_REG_COS3_WEIGHT_P0 ; 
 int PBF_REG_COS4_WEIGHT_P0 ; 
 int PBF_REG_COS5_WEIGHT_P0 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int const) ; 

__attribute__((used)) static int bnx2x_ets_e3b0_set_cos_bw(struct bnx2x *bp,
				     const u8 cos_entry,
				     const u32 min_w_val_nig,
				     const u32 min_w_val_pbf,
				     const u16 total_bw,
				     const u8 bw,
				     const u8 port)
{
	u32 nig_reg_adress_crd_weight = 0;
	u32 pbf_reg_adress_crd_weight = 0;
	/* Calculate and set BW for this COS - use 1 instead of 0 for BW */
	const u32 cos_bw_nig = ((bw ? bw : 1) * min_w_val_nig) / total_bw;
	const u32 cos_bw_pbf = ((bw ? bw : 1) * min_w_val_pbf) / total_bw;

	switch (cos_entry) {
	case 0:
		nig_reg_adress_crd_weight =
			(port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0 :
			NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0;
		pbf_reg_adress_crd_weight = (port) ?
		    PBF_REG_COS0_WEIGHT_P1 : PBF_REG_COS0_WEIGHT_P0;
		break;
	case 1:
		nig_reg_adress_crd_weight = (port) ?
			NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1 :
			NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1;
		pbf_reg_adress_crd_weight = (port) ?
			PBF_REG_COS1_WEIGHT_P1 : PBF_REG_COS1_WEIGHT_P0;
		break;
	case 2:
		nig_reg_adress_crd_weight = (port) ?
			NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2 :
			NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2;

		pbf_reg_adress_crd_weight = (port) ?
			PBF_REG_COS2_WEIGHT_P1 : PBF_REG_COS2_WEIGHT_P0;
		break;
	case 3:
		if (port)
			return -EINVAL;
		nig_reg_adress_crd_weight = NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3;
		pbf_reg_adress_crd_weight = PBF_REG_COS3_WEIGHT_P0;
		break;
	case 4:
		if (port)
			return -EINVAL;
		nig_reg_adress_crd_weight = NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4;
		pbf_reg_adress_crd_weight = PBF_REG_COS4_WEIGHT_P0;
		break;
	case 5:
		if (port)
			return -EINVAL;
		nig_reg_adress_crd_weight = NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5;
		pbf_reg_adress_crd_weight = PBF_REG_COS5_WEIGHT_P0;
		break;
	}

	REG_WR(bp, nig_reg_adress_crd_weight, cos_bw_nig);

	REG_WR(bp, pbf_reg_adress_crd_weight, cos_bw_pbf);

	return 0;
}