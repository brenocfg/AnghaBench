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
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct ni_power_info {TYPE_1__* cac_weights; int /*<<< orphan*/  cac_configuration_required; int /*<<< orphan*/  enable_cac; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_write_weight; int /*<<< orphan*/  mc_read_weight; int /*<<< orphan*/  gpr; int /*<<< orphan*/  vsp0; int /*<<< orphan*/  vsp; int /*<<< orphan*/  ovr_val_spare_1; int /*<<< orphan*/  ovr_mode_spare_1; int /*<<< orphan*/  ovr_val_spare_0; int /*<<< orphan*/  ovr_mode_spare_0; int /*<<< orphan*/  weight_sq_gpr; int /*<<< orphan*/  weight_sq_vsp0; int /*<<< orphan*/  weight_sq_vsp; int /*<<< orphan*/  weight_spare1; int /*<<< orphan*/  weight_spare0; int /*<<< orphan*/  weight_uvd_sig1; int /*<<< orphan*/  weight_uvd_sig0; int /*<<< orphan*/  weight_dc_sig3; int /*<<< orphan*/  weight_dc_sig2; int /*<<< orphan*/  weight_dc_sig1; int /*<<< orphan*/  weight_dc_sig0; int /*<<< orphan*/  weight_vgt_sig2; int /*<<< orphan*/  weight_vgt_sig1; int /*<<< orphan*/  weight_vgt_sig0; int /*<<< orphan*/  weight_pa_sig1; int /*<<< orphan*/  weight_pa_sig0; int /*<<< orphan*/  weight_cp; int /*<<< orphan*/  weight_bif; int /*<<< orphan*/  weight_sc; int /*<<< orphan*/  weight_lds_sig1; int /*<<< orphan*/  weight_lds_sig0; int /*<<< orphan*/  weight_spi_sig5; int /*<<< orphan*/  weight_spi_sig4; int /*<<< orphan*/  weight_spi_sig3; int /*<<< orphan*/  weight_spi_sig2; int /*<<< orphan*/  weight_spi_sig1; int /*<<< orphan*/  weight_spi_sig0; int /*<<< orphan*/  weight_xbr_2; int /*<<< orphan*/  weight_xbr_1; int /*<<< orphan*/  weight_xbr_0; int /*<<< orphan*/  weight_sxs_sig1; int /*<<< orphan*/  weight_sxs_sig0; int /*<<< orphan*/  weight_sxm_sig2; int /*<<< orphan*/  weight_sxm_sig1; int /*<<< orphan*/  weight_sxm_sig0; int /*<<< orphan*/  weight_db_sig3; int /*<<< orphan*/  weight_db_sig2; int /*<<< orphan*/  weight_db_sig1; int /*<<< orphan*/  weight_db_sig0; int /*<<< orphan*/  weight_cb_en3; int /*<<< orphan*/  weight_cb_en2; int /*<<< orphan*/  weight_cb_en1; int /*<<< orphan*/  weight_cb_en0; int /*<<< orphan*/  weight_tcc_en2; int /*<<< orphan*/  weight_tcc_en1; int /*<<< orphan*/  weight_tcc_en0; int /*<<< orphan*/  weight_ta_sig; int /*<<< orphan*/  weight_tcp_sig1; int /*<<< orphan*/  weight_tcp_sig0; } ;

/* Variables and functions */
 int ALLOW_OVERFLOW ; 
 int /*<<< orphan*/  CG_CAC_REGION_1_WEIGHT_0 ; 
 int /*<<< orphan*/  CG_CAC_REGION_1_WEIGHT_1 ; 
 int /*<<< orphan*/  CG_CAC_REGION_2_WEIGHT_0 ; 
 int /*<<< orphan*/  CG_CAC_REGION_2_WEIGHT_1 ; 
 int /*<<< orphan*/  CG_CAC_REGION_2_WEIGHT_2 ; 
 int /*<<< orphan*/  CG_CAC_REGION_3_WEIGHT_0 ; 
 int /*<<< orphan*/  CG_CAC_REGION_3_WEIGHT_1 ; 
 int /*<<< orphan*/  CG_CAC_REGION_4_OVERRIDE_4 ; 
 int /*<<< orphan*/  CG_CAC_REGION_4_WEIGHT_0 ; 
 int /*<<< orphan*/  CG_CAC_REGION_4_WEIGHT_1 ; 
 int /*<<< orphan*/  CG_CAC_REGION_4_WEIGHT_2 ; 
 int /*<<< orphan*/  CG_CAC_REGION_4_WEIGHT_3 ; 
 int /*<<< orphan*/  CG_CAC_REGION_5_WEIGHT_0 ; 
 int /*<<< orphan*/  CG_CAC_REGION_5_WEIGHT_1 ; 
 int EINVAL ; 
 int GPR (int /*<<< orphan*/ ) ; 
 int GPR_MASK ; 
 int INDEX (int) ; 
 int MCDW_WR_ENABLE ; 
 int MCDX_WR_ENABLE ; 
 int MCDY_WR_ENABLE ; 
 int MCDZ_WR_ENABLE ; 
 int /*<<< orphan*/  MC_CG_CONFIG ; 
 int /*<<< orphan*/  MC_CG_DATAPORT ; 
 int OVR_MODE_SPARE_0 (int /*<<< orphan*/ ) ; 
 int OVR_MODE_SPARE_0_MASK ; 
 int OVR_MODE_SPARE_1 (int /*<<< orphan*/ ) ; 
 int OVR_MODE_SPARE_1_MASK ; 
 int OVR_VAL_SPARE_0 (int /*<<< orphan*/ ) ; 
 int OVR_VAL_SPARE_0_MASK ; 
 int OVR_VAL_SPARE_1 (int /*<<< orphan*/ ) ; 
 int OVR_VAL_SPARE_1_MASK ; 
 int READ_WEIGHT (int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQ_CAC_THRESHOLD ; 
 int VSP (int /*<<< orphan*/ ) ; 
 int VSP0 (int /*<<< orphan*/ ) ; 
 int VSP0_MASK ; 
 int VSP_MASK ; 
 int WEIGHT_BIF (int /*<<< orphan*/ ) ; 
 int WEIGHT_BIF_MASK ; 
 int WEIGHT_CB_EN0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_CB_EN0_MASK ; 
 int WEIGHT_CB_EN1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_CB_EN1_MASK ; 
 int WEIGHT_CB_EN2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_CB_EN2_MASK ; 
 int WEIGHT_CB_EN3 (int /*<<< orphan*/ ) ; 
 int WEIGHT_CB_EN3_MASK ; 
 int WEIGHT_CP (int /*<<< orphan*/ ) ; 
 int WEIGHT_CP_MASK ; 
 int WEIGHT_DB_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DB_SIG0_MASK ; 
 int WEIGHT_DB_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DB_SIG1_MASK ; 
 int WEIGHT_DB_SIG2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DB_SIG2_MASK ; 
 int WEIGHT_DB_SIG3 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DB_SIG3_MASK ; 
 int WEIGHT_DC_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DC_SIG0_MASK ; 
 int WEIGHT_DC_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DC_SIG1_MASK ; 
 int WEIGHT_DC_SIG2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DC_SIG2_MASK ; 
 int WEIGHT_DC_SIG3 (int /*<<< orphan*/ ) ; 
 int WEIGHT_DC_SIG3_MASK ; 
 int WEIGHT_LDS_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_LDS_SIG0_MASK ; 
 int WEIGHT_LDS_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_LDS_SIG1_MASK ; 
 int WEIGHT_PA_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_PA_SIG0_MASK ; 
 int WEIGHT_PA_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_PA_SIG1_MASK ; 
 int WEIGHT_SC (int /*<<< orphan*/ ) ; 
 int WEIGHT_SC_MASK ; 
 int WEIGHT_SPARE0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPARE0_MASK ; 
 int WEIGHT_SPARE1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPARE1_MASK ; 
 int WEIGHT_SPI_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPI_SIG0_MASK ; 
 int WEIGHT_SPI_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPI_SIG1_MASK ; 
 int WEIGHT_SPI_SIG2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPI_SIG2_MASK ; 
 int WEIGHT_SPI_SIG3 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPI_SIG3_MASK ; 
 int WEIGHT_SPI_SIG4 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPI_SIG4_MASK ; 
 int WEIGHT_SPI_SIG5 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SPI_SIG5_MASK ; 
 int WEIGHT_SQ_GPR (int /*<<< orphan*/ ) ; 
 int WEIGHT_SQ_GPR_MASK ; 
 int WEIGHT_SQ_VSP (int /*<<< orphan*/ ) ; 
 int WEIGHT_SQ_VSP0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SQ_VSP0_MASK ; 
 int WEIGHT_SQ_VSP_MASK ; 
 int WEIGHT_SXM_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SXM_SIG0_MASK ; 
 int WEIGHT_SXM_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SXM_SIG1_MASK ; 
 int WEIGHT_SXM_SIG2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SXM_SIG2_MASK ; 
 int WEIGHT_SXS_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SXS_SIG0_MASK ; 
 int WEIGHT_SXS_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_SXS_SIG1_MASK ; 
 int WEIGHT_TA_SIG (int /*<<< orphan*/ ) ; 
 int WEIGHT_TA_SIG_MASK ; 
 int WEIGHT_TCC_EN0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_TCC_EN0_MASK ; 
 int WEIGHT_TCC_EN1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_TCC_EN1_MASK ; 
 int WEIGHT_TCC_EN2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_TCC_EN2_MASK ; 
 int WEIGHT_TCP_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_TCP_SIG0_MASK ; 
 int WEIGHT_TCP_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_TCP_SIG1_MASK ; 
 int WEIGHT_UVD_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_UVD_SIG0_MASK ; 
 int WEIGHT_UVD_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_UVD_SIG1_MASK ; 
 int WEIGHT_VGT_SIG0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_VGT_SIG0_MASK ; 
 int WEIGHT_VGT_SIG1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_VGT_SIG1_MASK ; 
 int WEIGHT_VGT_SIG2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_VGT_SIG2_MASK ; 
 int WEIGHT_XBR_0 (int /*<<< orphan*/ ) ; 
 int WEIGHT_XBR_0_MASK ; 
 int WEIGHT_XBR_1 (int /*<<< orphan*/ ) ; 
 int WEIGHT_XBR_1_MASK ; 
 int WEIGHT_XBR_2 (int /*<<< orphan*/ ) ; 
 int WEIGHT_XBR_2_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_CG (int /*<<< orphan*/ ,int) ; 
 int WRITE_WEIGHT (int /*<<< orphan*/ ) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ni_initialize_hardware_cac_manager(struct radeon_device *rdev)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	u32 reg;

	if (!ni_pi->enable_cac ||
	    !ni_pi->cac_configuration_required)
		return 0;

	if (ni_pi->cac_weights == NULL)
		return -EINVAL;

	reg = RREG32_CG(CG_CAC_REGION_1_WEIGHT_0) & ~(WEIGHT_TCP_SIG0_MASK |
						      WEIGHT_TCP_SIG1_MASK |
						      WEIGHT_TA_SIG_MASK);
	reg |= (WEIGHT_TCP_SIG0(ni_pi->cac_weights->weight_tcp_sig0) |
		WEIGHT_TCP_SIG1(ni_pi->cac_weights->weight_tcp_sig1) |
		WEIGHT_TA_SIG(ni_pi->cac_weights->weight_ta_sig));
	WREG32_CG(CG_CAC_REGION_1_WEIGHT_0, reg);

	reg = RREG32_CG(CG_CAC_REGION_1_WEIGHT_1) & ~(WEIGHT_TCC_EN0_MASK |
						      WEIGHT_TCC_EN1_MASK |
						      WEIGHT_TCC_EN2_MASK);
	reg |= (WEIGHT_TCC_EN0(ni_pi->cac_weights->weight_tcc_en0) |
		WEIGHT_TCC_EN1(ni_pi->cac_weights->weight_tcc_en1) |
		WEIGHT_TCC_EN2(ni_pi->cac_weights->weight_tcc_en2));
	WREG32_CG(CG_CAC_REGION_1_WEIGHT_1, reg);

	reg = RREG32_CG(CG_CAC_REGION_2_WEIGHT_0) & ~(WEIGHT_CB_EN0_MASK |
						      WEIGHT_CB_EN1_MASK |
						      WEIGHT_CB_EN2_MASK |
						      WEIGHT_CB_EN3_MASK);
	reg |= (WEIGHT_CB_EN0(ni_pi->cac_weights->weight_cb_en0) |
		WEIGHT_CB_EN1(ni_pi->cac_weights->weight_cb_en1) |
		WEIGHT_CB_EN2(ni_pi->cac_weights->weight_cb_en2) |
		WEIGHT_CB_EN3(ni_pi->cac_weights->weight_cb_en3));
	WREG32_CG(CG_CAC_REGION_2_WEIGHT_0, reg);

	reg = RREG32_CG(CG_CAC_REGION_2_WEIGHT_1) & ~(WEIGHT_DB_SIG0_MASK |
						      WEIGHT_DB_SIG1_MASK |
						      WEIGHT_DB_SIG2_MASK |
						      WEIGHT_DB_SIG3_MASK);
	reg |= (WEIGHT_DB_SIG0(ni_pi->cac_weights->weight_db_sig0) |
		WEIGHT_DB_SIG1(ni_pi->cac_weights->weight_db_sig1) |
		WEIGHT_DB_SIG2(ni_pi->cac_weights->weight_db_sig2) |
		WEIGHT_DB_SIG3(ni_pi->cac_weights->weight_db_sig3));
	WREG32_CG(CG_CAC_REGION_2_WEIGHT_1, reg);

	reg = RREG32_CG(CG_CAC_REGION_2_WEIGHT_2) & ~(WEIGHT_SXM_SIG0_MASK |
						      WEIGHT_SXM_SIG1_MASK |
						      WEIGHT_SXM_SIG2_MASK |
						      WEIGHT_SXS_SIG0_MASK |
						      WEIGHT_SXS_SIG1_MASK);
	reg |= (WEIGHT_SXM_SIG0(ni_pi->cac_weights->weight_sxm_sig0) |
		WEIGHT_SXM_SIG1(ni_pi->cac_weights->weight_sxm_sig1) |
		WEIGHT_SXM_SIG2(ni_pi->cac_weights->weight_sxm_sig2) |
		WEIGHT_SXS_SIG0(ni_pi->cac_weights->weight_sxs_sig0) |
		WEIGHT_SXS_SIG1(ni_pi->cac_weights->weight_sxs_sig1));
	WREG32_CG(CG_CAC_REGION_2_WEIGHT_2, reg);

	reg = RREG32_CG(CG_CAC_REGION_3_WEIGHT_0) & ~(WEIGHT_XBR_0_MASK |
						      WEIGHT_XBR_1_MASK |
						      WEIGHT_XBR_2_MASK |
						      WEIGHT_SPI_SIG0_MASK);
	reg |= (WEIGHT_XBR_0(ni_pi->cac_weights->weight_xbr_0) |
		WEIGHT_XBR_1(ni_pi->cac_weights->weight_xbr_1) |
		WEIGHT_XBR_2(ni_pi->cac_weights->weight_xbr_2) |
		WEIGHT_SPI_SIG0(ni_pi->cac_weights->weight_spi_sig0));
	WREG32_CG(CG_CAC_REGION_3_WEIGHT_0, reg);

	reg = RREG32_CG(CG_CAC_REGION_3_WEIGHT_1) & ~(WEIGHT_SPI_SIG1_MASK |
						      WEIGHT_SPI_SIG2_MASK |
						      WEIGHT_SPI_SIG3_MASK |
						      WEIGHT_SPI_SIG4_MASK |
						      WEIGHT_SPI_SIG5_MASK);
	reg |= (WEIGHT_SPI_SIG1(ni_pi->cac_weights->weight_spi_sig1) |
		WEIGHT_SPI_SIG2(ni_pi->cac_weights->weight_spi_sig2) |
		WEIGHT_SPI_SIG3(ni_pi->cac_weights->weight_spi_sig3) |
		WEIGHT_SPI_SIG4(ni_pi->cac_weights->weight_spi_sig4) |
		WEIGHT_SPI_SIG5(ni_pi->cac_weights->weight_spi_sig5));
	WREG32_CG(CG_CAC_REGION_3_WEIGHT_1, reg);

	reg = RREG32_CG(CG_CAC_REGION_4_WEIGHT_0) & ~(WEIGHT_LDS_SIG0_MASK |
						      WEIGHT_LDS_SIG1_MASK |
						      WEIGHT_SC_MASK);
	reg |= (WEIGHT_LDS_SIG0(ni_pi->cac_weights->weight_lds_sig0) |
		WEIGHT_LDS_SIG1(ni_pi->cac_weights->weight_lds_sig1) |
		WEIGHT_SC(ni_pi->cac_weights->weight_sc));
	WREG32_CG(CG_CAC_REGION_4_WEIGHT_0, reg);

	reg = RREG32_CG(CG_CAC_REGION_4_WEIGHT_1) & ~(WEIGHT_BIF_MASK |
						      WEIGHT_CP_MASK |
						      WEIGHT_PA_SIG0_MASK |
						      WEIGHT_PA_SIG1_MASK |
						      WEIGHT_VGT_SIG0_MASK);
	reg |= (WEIGHT_BIF(ni_pi->cac_weights->weight_bif) |
		WEIGHT_CP(ni_pi->cac_weights->weight_cp) |
		WEIGHT_PA_SIG0(ni_pi->cac_weights->weight_pa_sig0) |
		WEIGHT_PA_SIG1(ni_pi->cac_weights->weight_pa_sig1) |
		WEIGHT_VGT_SIG0(ni_pi->cac_weights->weight_vgt_sig0));
	WREG32_CG(CG_CAC_REGION_4_WEIGHT_1, reg);

	reg = RREG32_CG(CG_CAC_REGION_4_WEIGHT_2) & ~(WEIGHT_VGT_SIG1_MASK |
						      WEIGHT_VGT_SIG2_MASK |
						      WEIGHT_DC_SIG0_MASK |
						      WEIGHT_DC_SIG1_MASK |
						      WEIGHT_DC_SIG2_MASK);
	reg |= (WEIGHT_VGT_SIG1(ni_pi->cac_weights->weight_vgt_sig1) |
		WEIGHT_VGT_SIG2(ni_pi->cac_weights->weight_vgt_sig2) |
		WEIGHT_DC_SIG0(ni_pi->cac_weights->weight_dc_sig0) |
		WEIGHT_DC_SIG1(ni_pi->cac_weights->weight_dc_sig1) |
		WEIGHT_DC_SIG2(ni_pi->cac_weights->weight_dc_sig2));
	WREG32_CG(CG_CAC_REGION_4_WEIGHT_2, reg);

	reg = RREG32_CG(CG_CAC_REGION_4_WEIGHT_3) & ~(WEIGHT_DC_SIG3_MASK |
						      WEIGHT_UVD_SIG0_MASK |
						      WEIGHT_UVD_SIG1_MASK |
						      WEIGHT_SPARE0_MASK |
						      WEIGHT_SPARE1_MASK);
	reg |= (WEIGHT_DC_SIG3(ni_pi->cac_weights->weight_dc_sig3) |
		WEIGHT_UVD_SIG0(ni_pi->cac_weights->weight_uvd_sig0) |
		WEIGHT_UVD_SIG1(ni_pi->cac_weights->weight_uvd_sig1) |
		WEIGHT_SPARE0(ni_pi->cac_weights->weight_spare0) |
		WEIGHT_SPARE1(ni_pi->cac_weights->weight_spare1));
	WREG32_CG(CG_CAC_REGION_4_WEIGHT_3, reg);

	reg = RREG32_CG(CG_CAC_REGION_5_WEIGHT_0) & ~(WEIGHT_SQ_VSP_MASK |
						      WEIGHT_SQ_VSP0_MASK);
	reg |= (WEIGHT_SQ_VSP(ni_pi->cac_weights->weight_sq_vsp) |
		WEIGHT_SQ_VSP0(ni_pi->cac_weights->weight_sq_vsp0));
	WREG32_CG(CG_CAC_REGION_5_WEIGHT_0, reg);

	reg = RREG32_CG(CG_CAC_REGION_5_WEIGHT_1) & ~(WEIGHT_SQ_GPR_MASK);
	reg |= WEIGHT_SQ_GPR(ni_pi->cac_weights->weight_sq_gpr);
	WREG32_CG(CG_CAC_REGION_5_WEIGHT_1, reg);

	reg = RREG32_CG(CG_CAC_REGION_4_OVERRIDE_4) & ~(OVR_MODE_SPARE_0_MASK |
							OVR_VAL_SPARE_0_MASK |
							OVR_MODE_SPARE_1_MASK |
							OVR_VAL_SPARE_1_MASK);
	reg |= (OVR_MODE_SPARE_0(ni_pi->cac_weights->ovr_mode_spare_0) |
		OVR_VAL_SPARE_0(ni_pi->cac_weights->ovr_val_spare_0) |
		OVR_MODE_SPARE_1(ni_pi->cac_weights->ovr_mode_spare_1) |
		OVR_VAL_SPARE_1(ni_pi->cac_weights->ovr_val_spare_1));
	WREG32_CG(CG_CAC_REGION_4_OVERRIDE_4, reg);

	reg = RREG32(SQ_CAC_THRESHOLD) & ~(VSP_MASK |
					   VSP0_MASK |
					   GPR_MASK);
	reg |= (VSP(ni_pi->cac_weights->vsp) |
		VSP0(ni_pi->cac_weights->vsp0) |
		GPR(ni_pi->cac_weights->gpr));
	WREG32(SQ_CAC_THRESHOLD, reg);

	reg = (MCDW_WR_ENABLE |
	       MCDX_WR_ENABLE |
	       MCDY_WR_ENABLE |
	       MCDZ_WR_ENABLE |
	       INDEX(0x09D4));
	WREG32(MC_CG_CONFIG, reg);

	reg = (READ_WEIGHT(ni_pi->cac_weights->mc_read_weight) |
	       WRITE_WEIGHT(ni_pi->cac_weights->mc_write_weight) |
	       ALLOW_OVERFLOW);
	WREG32(MC_CG_DATAPORT, reg);

	return 0;
}