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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct csio_mb {int dummy; } ;
struct csio_hw {int num_pports; int /*<<< orphan*/  mb_mempool; TYPE_1__* pport; int /*<<< orphan*/  pfn; } ;
typedef  int /*<<< orphan*/  fw_port_cap32_t ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;
struct TYPE_2__ {int /*<<< orphan*/  link_cfg; int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FW_CAPS16 ; 
 scalar_t__ FW_CAPS32 ; 
 scalar_t__ FW_CAPS_UNKNOWN ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_PFVF ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_PFVF_PORT_CAPS32 ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  csio_init_link_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_link_l1cfg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int csio_mb_fw_retval (struct csio_mb*) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_mb_params (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mb_port (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mb_process_read_params_rsp (struct csio_hw*,struct csio_mb*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mb_process_read_port_rsp (struct csio_hw*,struct csio_mb*,int*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_enable_ports(struct csio_hw *hw)
{
	struct csio_mb  *mbp;
	u16 fw_caps = FW_CAPS_UNKNOWN;
	enum fw_retval retval;
	uint8_t portid;
	fw_port_cap32_t pcaps, acaps, rcaps;
	int i;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	for (i = 0; i < hw->num_pports; i++) {
		portid = hw->pport[i].portid;

		if (fw_caps == FW_CAPS_UNKNOWN) {
			u32 param, val;

			param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_PORT_CAPS32));
			val = 1;

			csio_mb_params(hw, mbp, CSIO_MB_DEFAULT_TMO,
				       hw->pfn, 0, 1, &param, &val, true,
				       NULL);

			if (csio_mb_issue(hw, mbp)) {
				csio_err(hw, "failed to issue FW_PARAMS_CMD(r) port:%d\n",
					 portid);
				mempool_free(mbp, hw->mb_mempool);
				return -EINVAL;
			}

			csio_mb_process_read_params_rsp(hw, mbp, &retval,
							0, NULL);
			fw_caps = retval ? FW_CAPS16 : FW_CAPS32;
		}

		/* Read PORT information */
		csio_mb_port(hw, mbp, CSIO_MB_DEFAULT_TMO, portid,
			     false, 0, fw_caps, NULL);

		if (csio_mb_issue(hw, mbp)) {
			csio_err(hw, "failed to issue FW_PORT_CMD(r) port:%d\n",
				 portid);
			mempool_free(mbp, hw->mb_mempool);
			return -EINVAL;
		}

		csio_mb_process_read_port_rsp(hw, mbp, &retval, fw_caps,
					      &pcaps, &acaps);
		if (retval != FW_SUCCESS) {
			csio_err(hw, "FW_PORT_CMD(r) port:%d failed: 0x%x\n",
				 portid, retval);
			mempool_free(mbp, hw->mb_mempool);
			return -EINVAL;
		}

		csio_init_link_config(&hw->pport[i].link_cfg, pcaps, acaps);

		csio_link_l1cfg(&hw->pport[i].link_cfg, fw_caps, &rcaps);

		/* Write back PORT information */
		csio_mb_port(hw, mbp, CSIO_MB_DEFAULT_TMO, portid,
			     true, rcaps, fw_caps, NULL);

		if (csio_mb_issue(hw, mbp)) {
			csio_err(hw, "failed to issue FW_PORT_CMD(w) port:%d\n",
				 portid);
			mempool_free(mbp, hw->mb_mempool);
			return -EINVAL;
		}

		retval = csio_mb_fw_retval(mbp);
		if (retval != FW_SUCCESS) {
			csio_err(hw, "FW_PORT_CMD(w) port:%d failed :0x%x\n",
				 portid, retval);
			mempool_free(mbp, hw->mb_mempool);
			return -EINVAL;
		}

	} /* For all ports */

	mempool_free(mbp, hw->mb_mempool);

	return 0;
}