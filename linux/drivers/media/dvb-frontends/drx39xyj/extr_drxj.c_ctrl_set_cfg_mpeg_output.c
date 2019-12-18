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
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;
struct drxj_data {int standard; int curr_symbol_rate; int mpeg_output_clock_rate; int /*<<< orphan*/  constellation; } ;
struct drx_demod_instance {scalar_t__ my_common_attr; scalar_t__ my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;
struct TYPE_2__ {int enable_mpeg_output; } ;
struct drx_common_attr {int sys_clock_freq; TYPE_1__ mpeg_cfg; } ;
struct drx_cfg_mpeg_output {int enable_mpeg_output; int static_clk; int insert_rs_byte; int enable_parallel; int invert_data; int invert_err; int invert_str; int invert_val; int invert_clk; } ;

/* Variables and functions */
 int DRXJ_MPEGOUTPUT_CLOCK_RATE_AUTO ; 
#define  DRX_CONSTELLATION_QAM128 136 
#define  DRX_CONSTELLATION_QAM16 135 
#define  DRX_CONSTELLATION_QAM256 134 
#define  DRX_CONSTELLATION_QAM32 133 
#define  DRX_CONSTELLATION_QAM64 132 
#define  DRX_STANDARD_8VSB 131 
#define  DRX_STANDARD_ITU_A 130 
#define  DRX_STANDARD_ITU_B 129 
#define  DRX_STANDARD_ITU_C 128 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FEC_OC_AVR_PARM_A__A ; 
 int FEC_OC_AVR_PARM_A__PRE ; 
 int /*<<< orphan*/  FEC_OC_AVR_PARM_B__A ; 
 int FEC_OC_AVR_PARM_B__PRE ; 
 int /*<<< orphan*/  FEC_OC_DTO_BURST_LEN__A ; 
 int FEC_OC_DTO_BURST_LEN__PRE ; 
 int FEC_OC_DTO_MODE_DYNAMIC__M ; 
 int FEC_OC_DTO_MODE_OFFSET_ENABLE__M ; 
 int /*<<< orphan*/  FEC_OC_DTO_MODE__A ; 
 int /*<<< orphan*/  FEC_OC_DTO_PERIOD__A ; 
 int /*<<< orphan*/  FEC_OC_DTO_RATE_HI__A ; 
 int FEC_OC_DTO_RATE_HI__M ; 
 int FEC_OC_DTO_RATE_LO_RATE_LO__M ; 
 int /*<<< orphan*/  FEC_OC_DTO_RATE_LO__A ; 
 int FEC_OC_FCT_MODE_RAT_ENA__M ; 
 int FEC_OC_FCT_MODE_VIRT_ENA__M ; 
 int /*<<< orphan*/  FEC_OC_FCT_MODE__A ; 
 int /*<<< orphan*/  FEC_OC_FCT_USAGE__A ; 
 int FEC_OC_FCT_USAGE__PRE ; 
 int FEC_OC_IPR_INVERT_MCLK__M ; 
 int FEC_OC_IPR_INVERT_MD0__M ; 
 int FEC_OC_IPR_INVERT_MD1__M ; 
 int FEC_OC_IPR_INVERT_MD2__M ; 
 int FEC_OC_IPR_INVERT_MD3__M ; 
 int FEC_OC_IPR_INVERT_MD4__M ; 
 int FEC_OC_IPR_INVERT_MD5__M ; 
 int FEC_OC_IPR_INVERT_MD6__M ; 
 int FEC_OC_IPR_INVERT_MD7__M ; 
 int FEC_OC_IPR_INVERT_MERR__M ; 
 int FEC_OC_IPR_INVERT_MSTRT__M ; 
 int FEC_OC_IPR_INVERT_MVAL__M ; 
 int /*<<< orphan*/  FEC_OC_IPR_INVERT__A ; 
 int FEC_OC_IPR_MODE_MVAL_DIS_PAR__M ; 
 int FEC_OC_IPR_MODE_SERIAL__M ; 
 int /*<<< orphan*/  FEC_OC_IPR_MODE__A ; 
 int FEC_OC_MODE_PARITY__M ; 
 int FEC_OC_MODE_TRANSPARENT__M ; 
 int /*<<< orphan*/  FEC_OC_MODE__A ; 
 int /*<<< orphan*/  FEC_OC_OCR_INVERT__A ; 
 int /*<<< orphan*/  FEC_OC_RCN_CTL_RATE_LO__A ; 
 int /*<<< orphan*/  FEC_OC_RCN_GAIN__A ; 
 int FEC_OC_RCN_GAIN__PRE ; 
 int /*<<< orphan*/  FEC_OC_SNC_HWM__A ; 
 int /*<<< orphan*/  FEC_OC_SNC_LWM__A ; 
 int /*<<< orphan*/  FEC_OC_TMD_CTL_UPD_RATE__A ; 
 int FEC_OC_TMD_CTL_UPD_RATE__PRE ; 
 int /*<<< orphan*/  FEC_OC_TMD_INT_UPD_RATE__A ; 
 int MPEG_OUTPUT_CLK_DRIVE_STRENGTH ; 
 int MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH ; 
 int MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH ; 
 int SIO_PDR_MCLK_CFG_DRIVE__B ; 
 int SIO_PDR_MCLK_CFG_MODE__B ; 
 int /*<<< orphan*/  SIO_PDR_MCLK_CFG__A ; 
 int SIO_PDR_MD0_CFG_DRIVE__B ; 
 int SIO_PDR_MD0_CFG_MODE__B ; 
 int /*<<< orphan*/  SIO_PDR_MD0_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD1_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD2_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD3_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD4_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD5_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD6_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MD7_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MERR_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MON_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MSTRT_CFG__A ; 
 int /*<<< orphan*/  SIO_PDR_MVAL_CFG__A ; 
 int /*<<< orphan*/  SIO_TOP_COMM_KEY__A ; 
 int drxdap_fasi_write_reg32 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int frac28 (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int
ctrl_set_cfg_mpeg_output(struct drx_demod_instance *demod, struct drx_cfg_mpeg_output *cfg_data)
{
	struct i2c_device_addr *dev_addr = (struct i2c_device_addr *)(NULL);
	struct drxj_data *ext_attr = (struct drxj_data *) (NULL);
	struct drx_common_attr *common_attr = (struct drx_common_attr *) (NULL);
	int rc;
	u16 fec_oc_reg_mode = 0;
	u16 fec_oc_reg_ipr_mode = 0;
	u16 fec_oc_reg_ipr_invert = 0;
	u32 max_bit_rate = 0;
	u32 rcn_rate = 0;
	u32 nr_bits = 0;
	u16 sio_pdr_md_cfg = 0;
	/* data mask for the output data byte */
	u16 invert_data_mask =
	    FEC_OC_IPR_INVERT_MD7__M | FEC_OC_IPR_INVERT_MD6__M |
	    FEC_OC_IPR_INVERT_MD5__M | FEC_OC_IPR_INVERT_MD4__M |
	    FEC_OC_IPR_INVERT_MD3__M | FEC_OC_IPR_INVERT_MD2__M |
	    FEC_OC_IPR_INVERT_MD1__M | FEC_OC_IPR_INVERT_MD0__M;

	/* check arguments */
	if ((demod == NULL) || (cfg_data == NULL))
		return -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;
	common_attr = (struct drx_common_attr *) demod->my_common_attr;

	if (cfg_data->enable_mpeg_output == true) {
		/* quick and dirty patch to set MPEG in case current std is not
		   producing MPEG */
		switch (ext_attr->standard) {
		case DRX_STANDARD_8VSB:
		case DRX_STANDARD_ITU_A:
		case DRX_STANDARD_ITU_B:
		case DRX_STANDARD_ITU_C:
			break;
		default:
			return 0;
		}

		rc = drxj_dap_write_reg16(dev_addr, FEC_OC_OCR_INVERT__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		switch (ext_attr->standard) {
		case DRX_STANDARD_8VSB:
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_FCT_USAGE__A, 7, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* 2048 bytes fifo ram */
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_TMD_CTL_UPD_RATE__A, 10, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_TMD_INT_UPD_RATE__A, 10, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_AVR_PARM_A__A, 5, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_AVR_PARM_B__A, 7, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_RCN_GAIN__A, 10, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			/* Low Water Mark for synchronization  */
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_SNC_LWM__A, 3, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			/* High Water Mark for synchronization */
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_SNC_HWM__A, 5, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		case DRX_STANDARD_ITU_A:
		case DRX_STANDARD_ITU_C:
			switch (ext_attr->constellation) {
			case DRX_CONSTELLATION_QAM256:
				nr_bits = 8;
				break;
			case DRX_CONSTELLATION_QAM128:
				nr_bits = 7;
				break;
			case DRX_CONSTELLATION_QAM64:
				nr_bits = 6;
				break;
			case DRX_CONSTELLATION_QAM32:
				nr_bits = 5;
				break;
			case DRX_CONSTELLATION_QAM16:
				nr_bits = 4;
				break;
			default:
				return -EIO;
			}	/* ext_attr->constellation */
			/* max_bit_rate = symbol_rate * nr_bits * coef */
			/* coef = 188/204                          */
			max_bit_rate =
			    (ext_attr->curr_symbol_rate / 8) * nr_bits * 188;
			/* fall-through - as b/c Annex A/C need following settings */
		case DRX_STANDARD_ITU_B:
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_FCT_USAGE__A, FEC_OC_FCT_USAGE__PRE, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_TMD_CTL_UPD_RATE__A, FEC_OC_TMD_CTL_UPD_RATE__PRE, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_TMD_INT_UPD_RATE__A, 5, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_AVR_PARM_A__A, FEC_OC_AVR_PARM_A__PRE, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_AVR_PARM_B__A, FEC_OC_AVR_PARM_B__PRE, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			if (cfg_data->static_clk == true) {
				rc = drxj_dap_write_reg16(dev_addr, FEC_OC_RCN_GAIN__A, 0xD, 0);
				if (rc != 0) {
					pr_err("error %d\n", rc);
					goto rw_error;
				}
			} else {
				rc = drxj_dap_write_reg16(dev_addr, FEC_OC_RCN_GAIN__A, FEC_OC_RCN_GAIN__PRE, 0);
				if (rc != 0) {
					pr_err("error %d\n", rc);
					goto rw_error;
				}
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_SNC_LWM__A, 2, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_SNC_HWM__A, 12, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		default:
			break;
		}		/* switch (standard) */

		/* Check insertion of the Reed-Solomon parity bytes */
		rc = drxj_dap_read_reg16(dev_addr, FEC_OC_MODE__A, &fec_oc_reg_mode, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_read_reg16(dev_addr, FEC_OC_IPR_MODE__A, &fec_oc_reg_ipr_mode, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (cfg_data->insert_rs_byte == true) {
			/* enable parity symbol forward */
			fec_oc_reg_mode |= FEC_OC_MODE_PARITY__M;
			/* MVAL disable during parity bytes */
			fec_oc_reg_ipr_mode |= FEC_OC_IPR_MODE_MVAL_DIS_PAR__M;
			switch (ext_attr->standard) {
			case DRX_STANDARD_8VSB:
				rcn_rate = 0x004854D3;
				break;
			case DRX_STANDARD_ITU_B:
				fec_oc_reg_mode |= FEC_OC_MODE_TRANSPARENT__M;
				switch (ext_attr->constellation) {
				case DRX_CONSTELLATION_QAM256:
					rcn_rate = 0x008945E7;
					break;
				case DRX_CONSTELLATION_QAM64:
					rcn_rate = 0x005F64D4;
					break;
				default:
					return -EIO;
				}
				break;
			case DRX_STANDARD_ITU_A:
			case DRX_STANDARD_ITU_C:
				/* insert_rs_byte = true -> coef = 188/188 -> 1, RS bits are in MPEG output */
				rcn_rate =
				    (frac28
				     (max_bit_rate,
				      (u32) (common_attr->sys_clock_freq / 8))) /
				    188;
				break;
			default:
				return -EIO;
			}	/* ext_attr->standard */
		} else {	/* insert_rs_byte == false */

			/* disable parity symbol forward */
			fec_oc_reg_mode &= (~FEC_OC_MODE_PARITY__M);
			/* MVAL enable during parity bytes */
			fec_oc_reg_ipr_mode &= (~FEC_OC_IPR_MODE_MVAL_DIS_PAR__M);
			switch (ext_attr->standard) {
			case DRX_STANDARD_8VSB:
				rcn_rate = 0x0041605C;
				break;
			case DRX_STANDARD_ITU_B:
				fec_oc_reg_mode &= (~FEC_OC_MODE_TRANSPARENT__M);
				switch (ext_attr->constellation) {
				case DRX_CONSTELLATION_QAM256:
					rcn_rate = 0x0082D6A0;
					break;
				case DRX_CONSTELLATION_QAM64:
					rcn_rate = 0x005AEC1A;
					break;
				default:
					return -EIO;
				}
				break;
			case DRX_STANDARD_ITU_A:
			case DRX_STANDARD_ITU_C:
				/* insert_rs_byte = false -> coef = 188/204, RS bits not in MPEG output */
				rcn_rate =
				    (frac28
				     (max_bit_rate,
				      (u32) (common_attr->sys_clock_freq / 8))) /
				    204;
				break;
			default:
				return -EIO;
			}	/* ext_attr->standard */
		}

		if (cfg_data->enable_parallel == true) {	/* MPEG data output is parallel -> clear ipr_mode[0] */
			fec_oc_reg_ipr_mode &= (~(FEC_OC_IPR_MODE_SERIAL__M));
		} else {	/* MPEG data output is serial -> set ipr_mode[0] */
			fec_oc_reg_ipr_mode |= FEC_OC_IPR_MODE_SERIAL__M;
		}

		/* Control slective inversion of output bits */
		if (cfg_data->invert_data == true)
			fec_oc_reg_ipr_invert |= invert_data_mask;
		else
			fec_oc_reg_ipr_invert &= (~(invert_data_mask));

		if (cfg_data->invert_err == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MERR__M;
		else
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MERR__M));

		if (cfg_data->invert_str == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MSTRT__M;
		else
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MSTRT__M));

		if (cfg_data->invert_val == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MVAL__M;
		else
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MVAL__M));

		if (cfg_data->invert_clk == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MCLK__M;
		else
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MCLK__M));


		if (cfg_data->static_clk == true) {	/* Static mode */
			u32 dto_rate = 0;
			u32 bit_rate = 0;
			u16 fec_oc_dto_burst_len = 0;
			u16 fec_oc_dto_period = 0;

			fec_oc_dto_burst_len = FEC_OC_DTO_BURST_LEN__PRE;

			switch (ext_attr->standard) {
			case DRX_STANDARD_8VSB:
				fec_oc_dto_period = 4;
				if (cfg_data->insert_rs_byte == true)
					fec_oc_dto_burst_len = 208;
				break;
			case DRX_STANDARD_ITU_A:
				{
					u32 symbol_rate_th = 6400000;
					if (cfg_data->insert_rs_byte == true) {
						fec_oc_dto_burst_len = 204;
						symbol_rate_th = 5900000;
					}
					if (ext_attr->curr_symbol_rate >=
					    symbol_rate_th) {
						fec_oc_dto_period = 0;
					} else {
						fec_oc_dto_period = 1;
					}
				}
				break;
			case DRX_STANDARD_ITU_B:
				fec_oc_dto_period = 1;
				if (cfg_data->insert_rs_byte == true)
					fec_oc_dto_burst_len = 128;
				break;
			case DRX_STANDARD_ITU_C:
				fec_oc_dto_period = 1;
				if (cfg_data->insert_rs_byte == true)
					fec_oc_dto_burst_len = 204;
				break;
			default:
				return -EIO;
			}
			bit_rate =
			    common_attr->sys_clock_freq * 1000 / (fec_oc_dto_period +
							       2);
			dto_rate =
			    frac28(bit_rate, common_attr->sys_clock_freq * 1000);
			dto_rate >>= 3;
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_DTO_RATE_HI__A, (u16)((dto_rate >> 16) & FEC_OC_DTO_RATE_HI__M), 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_DTO_RATE_LO__A, (u16)(dto_rate & FEC_OC_DTO_RATE_LO_RATE_LO__M), 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_DTO_MODE__A, FEC_OC_DTO_MODE_DYNAMIC__M | FEC_OC_DTO_MODE_OFFSET_ENABLE__M, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_FCT_MODE__A, FEC_OC_FCT_MODE_RAT_ENA__M | FEC_OC_FCT_MODE_VIRT_ENA__M, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_DTO_BURST_LEN__A, fec_oc_dto_burst_len, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			if (ext_attr->mpeg_output_clock_rate != DRXJ_MPEGOUTPUT_CLOCK_RATE_AUTO)
				fec_oc_dto_period = ext_attr->mpeg_output_clock_rate - 1;
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_DTO_PERIOD__A, fec_oc_dto_period, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		} else {	/* Dynamic mode */

			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_DTO_MODE__A, FEC_OC_DTO_MODE_DYNAMIC__M, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, FEC_OC_FCT_MODE__A, 0, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		}

		rc = drxdap_fasi_write_reg32(dev_addr, FEC_OC_RCN_CTL_RATE_LO__A, rcn_rate, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		/* Write appropriate registers with requested configuration */
		rc = drxj_dap_write_reg16(dev_addr, FEC_OC_MODE__A, fec_oc_reg_mode, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, FEC_OC_IPR_MODE__A, fec_oc_reg_ipr_mode, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, FEC_OC_IPR_INVERT__A, fec_oc_reg_ipr_invert, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		/* enabling for both parallel and serial now */
		/*  Write magic word to enable pdr reg write */
		rc = drxj_dap_write_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0xFABA, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		/*  Set MPEG TS pads to outputmode */
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MSTRT_CFG__A, 0x0013, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MERR_CFG__A, 0x0013, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MCLK_CFG__A, MPEG_OUTPUT_CLK_DRIVE_STRENGTH << SIO_PDR_MCLK_CFG_DRIVE__B | 0x03 << SIO_PDR_MCLK_CFG_MODE__B, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MVAL_CFG__A, 0x0013, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		sio_pdr_md_cfg =
		    MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH <<
		    SIO_PDR_MD0_CFG_DRIVE__B | 0x03 << SIO_PDR_MD0_CFG_MODE__B;
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD0_CFG__A, sio_pdr_md_cfg, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (cfg_data->enable_parallel == true) {	/* MPEG data output is parallel -> set MD1 to MD7 to output mode */
			sio_pdr_md_cfg =
			    MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH <<
			    SIO_PDR_MD0_CFG_DRIVE__B | 0x03 <<
			    SIO_PDR_MD0_CFG_MODE__B;
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD0_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD1_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD2_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD3_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD4_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD5_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD6_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD7_CFG__A, sio_pdr_md_cfg, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		} else {	/* MPEG data output is serial -> set MD1 to MD7 to tri-state */
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD1_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD2_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD3_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD4_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD5_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD6_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD7_CFG__A, 0x0000, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		}
		/*  Enable Monitor Bus output over MPEG pads and ctl input */
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MON_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		/*  Write nomagic word to enable pdr reg write */
		rc = drxj_dap_write_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	} else {
		/*  Write magic word to enable pdr reg write */
		rc = drxj_dap_write_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0xFABA, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		/*  Set MPEG TS pads to inputmode */
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MSTRT_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MERR_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MCLK_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MVAL_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD0_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD1_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD2_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD3_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD4_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD5_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD6_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MD7_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		/* Enable Monitor Bus output over MPEG pads and ctl input */
		rc = drxj_dap_write_reg16(dev_addr, SIO_PDR_MON_CFG__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		/* Write nomagic word to enable pdr reg write */
		rc = drxj_dap_write_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}

	/* save values for restore after re-acquire */
	common_attr->mpeg_cfg.enable_mpeg_output = cfg_data->enable_mpeg_output;

	return 0;
rw_error:
	return rc;
}