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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_4__ {int* param_val; } ;
struct dbg_tools_data {TYPE_2__ grc; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_3__ {size_t engine_for_debug; } ;
struct qed_dev {int num_hwfns; TYPE_1__ dbg_params; struct qed_hwfn* hwfns; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CFG ; 
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*,int,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  FW_ASSERTS ; 
 int /*<<< orphan*/  GRC_DUMP ; 
 int /*<<< orphan*/  IDLE_CHK ; 
 int /*<<< orphan*/  IGU_FIFO ; 
 int MAX_DBG_GRC_PARAMS ; 
 int /*<<< orphan*/  MCP_TRACE ; 
 int /*<<< orphan*/  NVM_CFG1 ; 
 int /*<<< orphan*/  NVM_META ; 
 int /*<<< orphan*/  PROTECTION_OVERRIDE ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int /*<<< orphan*/  QED_NVM_IMAGE_DEFAULT_CFG ; 
 int /*<<< orphan*/  QED_NVM_IMAGE_NVM_CFG1 ; 
 int /*<<< orphan*/  QED_NVM_IMAGE_NVM_META ; 
 int REGDUMP_HEADER_SIZE ; 
 int /*<<< orphan*/  REG_FIFO ; 
 int qed_calc_regdump_header (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int qed_dbg_fw_asserts (struct qed_dev*,scalar_t__*,int*) ; 
 int qed_dbg_grc (struct qed_dev*,scalar_t__*,int*) ; 
 int qed_dbg_idle_chk (struct qed_dev*,scalar_t__*,int*) ; 
 int qed_dbg_igu_fifo (struct qed_dev*,scalar_t__*,int*) ; 
 int qed_dbg_mcp_trace (struct qed_dev*,scalar_t__*,int*) ; 
 int qed_dbg_nvm_image (struct qed_dev*,scalar_t__*,int*,int /*<<< orphan*/ ) ; 
 int qed_dbg_protection_override (struct qed_dev*,scalar_t__*,int*) ; 
 int qed_dbg_reg_fifo (struct qed_dev*,scalar_t__*,int*) ; 
 scalar_t__ qed_get_debug_engine (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_set_debug_engine (struct qed_dev*,scalar_t__) ; 

int qed_dbg_all_data(struct qed_dev *cdev, void *buffer)
{
	u8 cur_engine, omit_engine = 0, org_engine;
	struct qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->dbg_params.engine_for_debug];
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	int grc_params[MAX_DBG_GRC_PARAMS], i;
	u32 offset = 0, feature_size;
	int rc;

	for (i = 0; i < MAX_DBG_GRC_PARAMS; i++)
		grc_params[i] = dev_data->grc.param_val[i];

	if (cdev->num_hwfns == 1)
		omit_engine = 1;

	org_engine = qed_get_debug_engine(cdev);
	for (cur_engine = 0; cur_engine < cdev->num_hwfns; cur_engine++) {
		/* Collect idle_chks and grcDump for each hw function */
		DP_VERBOSE(cdev, QED_MSG_DEBUG,
			   "obtaining idle_chk and grcdump for current engine\n");
		qed_set_debug_engine(cdev, cur_engine);

		/* First idle_chk */
		rc = qed_dbg_idle_chk(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(IDLE_CHK, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev, "qed_dbg_idle_chk failed. rc = %d\n", rc);
		}

		/* Second idle_chk */
		rc = qed_dbg_idle_chk(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(IDLE_CHK, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev, "qed_dbg_idle_chk failed. rc = %d\n", rc);
		}

		/* reg_fifo dump */
		rc = qed_dbg_reg_fifo(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(REG_FIFO, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev, "qed_dbg_reg_fifo failed. rc = %d\n", rc);
		}

		/* igu_fifo dump */
		rc = qed_dbg_igu_fifo(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(IGU_FIFO, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev, "qed_dbg_igu_fifo failed. rc = %d", rc);
		}

		/* protection_override dump */
		rc = qed_dbg_protection_override(cdev, (u8 *)buffer + offset +
						 REGDUMP_HEADER_SIZE,
						 &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(PROTECTION_OVERRIDE,
						    cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev,
			       "qed_dbg_protection_override failed. rc = %d\n",
			       rc);
		}

		/* fw_asserts dump */
		rc = qed_dbg_fw_asserts(cdev, (u8 *)buffer + offset +
					REGDUMP_HEADER_SIZE, &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(FW_ASSERTS, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev, "qed_dbg_fw_asserts failed. rc = %d\n",
			       rc);
		}

		for (i = 0; i < MAX_DBG_GRC_PARAMS; i++)
			dev_data->grc.param_val[i] = grc_params[i];

		/* GRC dump - must be last because when mcp stuck it will
		 * clutter idle_chk, reg_fifo, ...
		 */
		rc = qed_dbg_grc(cdev, (u8 *)buffer + offset +
				 REGDUMP_HEADER_SIZE, &feature_size);
		if (!rc) {
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(GRC_DUMP, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		} else {
			DP_ERR(cdev, "qed_dbg_grc failed. rc = %d", rc);
		}
	}

	qed_set_debug_engine(cdev, org_engine);
	/* mcp_trace */
	rc = qed_dbg_mcp_trace(cdev, (u8 *)buffer + offset +
			       REGDUMP_HEADER_SIZE, &feature_size);
	if (!rc) {
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(MCP_TRACE, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	} else {
		DP_ERR(cdev, "qed_dbg_mcp_trace failed. rc = %d\n", rc);
	}

	/* nvm cfg1 */
	rc = qed_dbg_nvm_image(cdev,
			       (u8 *)buffer + offset + REGDUMP_HEADER_SIZE,
			       &feature_size, QED_NVM_IMAGE_NVM_CFG1);
	if (!rc) {
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(NVM_CFG1, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	} else if (rc != -ENOENT) {
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image  %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_NVM_CFG1, "QED_NVM_IMAGE_NVM_CFG1", rc);
	}

	/* nvm default */
	rc = qed_dbg_nvm_image(cdev,
			       (u8 *)buffer + offset + REGDUMP_HEADER_SIZE,
			       &feature_size, QED_NVM_IMAGE_DEFAULT_CFG);
	if (!rc) {
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(DEFAULT_CFG, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	} else if (rc != -ENOENT) {
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_DEFAULT_CFG, "QED_NVM_IMAGE_DEFAULT_CFG",
		       rc);
	}

	/* nvm meta */
	rc = qed_dbg_nvm_image(cdev,
			       (u8 *)buffer + offset + REGDUMP_HEADER_SIZE,
			       &feature_size, QED_NVM_IMAGE_NVM_META);
	if (!rc) {
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(NVM_META, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	} else if (rc != -ENOENT) {
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_NVM_META, "QED_NVM_IMAGE_NVM_META", rc);
	}

	return 0;
}