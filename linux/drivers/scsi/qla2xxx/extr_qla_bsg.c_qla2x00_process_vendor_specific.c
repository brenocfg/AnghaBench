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
struct TYPE_3__ {int* vendor_cmd; } ;
struct TYPE_4__ {TYPE_1__ h_vendor; } ;
struct fc_bsg_request {TYPE_2__ rqst_data; } ;
struct bsg_job {struct fc_bsg_request* request; } ;

/* Variables and functions */
 int ENOSYS ; 
#define  QL_VND_A84_MGMT_CMD 151 
#define  QL_VND_A84_RESET 150 
#define  QL_VND_A84_UPDATE_FW 149 
#define  QL_VND_DIAG_IO_CMD 148 
#define  QL_VND_DPORT_DIAGNOSTICS 147 
#define  QL_VND_FCP_PRIO_CFG_CMD 146 
#define  QL_VND_FX00_MGMT_CMD 145 
#define  QL_VND_GET_BBCR_DATA 144 
#define  QL_VND_GET_FLASH_UPDATE_CAPS 143 
#define  QL_VND_GET_PRIV_STATS 142 
#define  QL_VND_GET_PRIV_STATS_EX 141 
#define  QL_VND_IIDMA 140 
#define  QL_VND_LOOPBACK 139 
#define  QL_VND_READ_FLASH 138 
#define  QL_VND_READ_FRU_STATUS 137 
#define  QL_VND_READ_I2C 136 
#define  QL_VND_SERDES_OP 135 
#define  QL_VND_SERDES_OP_EX 134 
#define  QL_VND_SET_FLASH_UPDATE_CAPS 133 
#define  QL_VND_SET_FRU_VERSION 132 
#define  QL_VND_SS_GET_FLASH_IMAGE_STATUS 131 
#define  QL_VND_UPDATE_FLASH 130 
#define  QL_VND_WRITE_FRU_STATUS 129 
#define  QL_VND_WRITE_I2C 128 
 int qla24xx_iidma (struct bsg_job*) ; 
 int qla24xx_proc_fcp_prio_cfg_cmd (struct bsg_job*) ; 
 int qla24xx_process_bidir_cmd (struct bsg_job*) ; 
 int qla26xx_serdes_op (struct bsg_job*) ; 
 int qla27xx_get_bbcr_data (struct bsg_job*) ; 
 int qla27xx_get_flash_upd_cap (struct bsg_job*) ; 
 int qla27xx_set_flash_upd_cap (struct bsg_job*) ; 
 int qla2x00_do_dport_diagnostics (struct bsg_job*) ; 
 int qla2x00_get_flash_image_status (struct bsg_job*) ; 
 int qla2x00_get_priv_stats (struct bsg_job*) ; 
 int qla2x00_process_loopback (struct bsg_job*) ; 
 int qla2x00_read_fru_status (struct bsg_job*) ; 
 int qla2x00_read_i2c (struct bsg_job*) ; 
 int qla2x00_read_optrom (struct bsg_job*) ; 
 int qla2x00_update_fru_versions (struct bsg_job*) ; 
 int qla2x00_update_optrom (struct bsg_job*) ; 
 int qla2x00_write_fru_status (struct bsg_job*) ; 
 int qla2x00_write_i2c (struct bsg_job*) ; 
 int qla8044_serdes_op (struct bsg_job*) ; 
 int qla84xx_mgmt_cmd (struct bsg_job*) ; 
 int qla84xx_reset (struct bsg_job*) ; 
 int qla84xx_updatefw (struct bsg_job*) ; 
 int qlafx00_mgmt_cmd (struct bsg_job*) ; 

__attribute__((used)) static int
qla2x00_process_vendor_specific(struct bsg_job *bsg_job)
{
	struct fc_bsg_request *bsg_request = bsg_job->request;

	switch (bsg_request->rqst_data.h_vendor.vendor_cmd[0]) {
	case QL_VND_LOOPBACK:
		return qla2x00_process_loopback(bsg_job);

	case QL_VND_A84_RESET:
		return qla84xx_reset(bsg_job);

	case QL_VND_A84_UPDATE_FW:
		return qla84xx_updatefw(bsg_job);

	case QL_VND_A84_MGMT_CMD:
		return qla84xx_mgmt_cmd(bsg_job);

	case QL_VND_IIDMA:
		return qla24xx_iidma(bsg_job);

	case QL_VND_FCP_PRIO_CFG_CMD:
		return qla24xx_proc_fcp_prio_cfg_cmd(bsg_job);

	case QL_VND_READ_FLASH:
		return qla2x00_read_optrom(bsg_job);

	case QL_VND_UPDATE_FLASH:
		return qla2x00_update_optrom(bsg_job);

	case QL_VND_SET_FRU_VERSION:
		return qla2x00_update_fru_versions(bsg_job);

	case QL_VND_READ_FRU_STATUS:
		return qla2x00_read_fru_status(bsg_job);

	case QL_VND_WRITE_FRU_STATUS:
		return qla2x00_write_fru_status(bsg_job);

	case QL_VND_WRITE_I2C:
		return qla2x00_write_i2c(bsg_job);

	case QL_VND_READ_I2C:
		return qla2x00_read_i2c(bsg_job);

	case QL_VND_DIAG_IO_CMD:
		return qla24xx_process_bidir_cmd(bsg_job);

	case QL_VND_FX00_MGMT_CMD:
		return qlafx00_mgmt_cmd(bsg_job);

	case QL_VND_SERDES_OP:
		return qla26xx_serdes_op(bsg_job);

	case QL_VND_SERDES_OP_EX:
		return qla8044_serdes_op(bsg_job);

	case QL_VND_GET_FLASH_UPDATE_CAPS:
		return qla27xx_get_flash_upd_cap(bsg_job);

	case QL_VND_SET_FLASH_UPDATE_CAPS:
		return qla27xx_set_flash_upd_cap(bsg_job);

	case QL_VND_GET_BBCR_DATA:
		return qla27xx_get_bbcr_data(bsg_job);

	case QL_VND_GET_PRIV_STATS:
	case QL_VND_GET_PRIV_STATS_EX:
		return qla2x00_get_priv_stats(bsg_job);

	case QL_VND_DPORT_DIAGNOSTICS:
		return qla2x00_do_dport_diagnostics(bsg_job);

	case QL_VND_SS_GET_FLASH_IMAGE_STATUS:
		return qla2x00_get_flash_image_status(bsg_job);

	default:
		return -ENOSYS;
	}
}