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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_io_buf {struct fcp_rsp* fcp_rsp; } ;
struct fcp_rsp {int rspStatus2; int rspInfo3; int /*<<< orphan*/  rspRspLen; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int RSP_LEN_VALID ; 
#define  RSP_NO_FAILURE 131 
#define  RSP_TM_INVALID_LU 130 
#define  RSP_TM_NOT_COMPLETED 129 
#define  RSP_TM_NOT_SUPPORTED 128 
 int SUCCESS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
lpfc_check_fcp_rsp(struct lpfc_vport *vport, struct lpfc_io_buf *lpfc_cmd)
{
	struct fcp_rsp *fcprsp = lpfc_cmd->fcp_rsp;
	uint32_t rsp_info;
	uint32_t rsp_len;
	uint8_t  rsp_info_code;
	int ret = FAILED;


	if (fcprsp == NULL)
		lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
				 "0703 fcp_rsp is missing\n");
	else {
		rsp_info = fcprsp->rspStatus2;
		rsp_len = be32_to_cpu(fcprsp->rspRspLen);
		rsp_info_code = fcprsp->rspInfo3;


		lpfc_printf_vlog(vport, KERN_INFO,
				 LOG_FCP,
				 "0706 fcp_rsp valid 0x%x,"
				 " rsp len=%d code 0x%x\n",
				 rsp_info,
				 rsp_len, rsp_info_code);

		/* If FCP_RSP_LEN_VALID bit is one, then the FCP_RSP_LEN
		 * field specifies the number of valid bytes of FCP_RSP_INFO.
		 * The FCP_RSP_LEN field shall be set to 0x04 or 0x08
		 */
		if ((fcprsp->rspStatus2 & RSP_LEN_VALID) &&
		    ((rsp_len == 8) || (rsp_len == 4))) {
			switch (rsp_info_code) {
			case RSP_NO_FAILURE:
				lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
						 "0715 Task Mgmt No Failure\n");
				ret = SUCCESS;
				break;
			case RSP_TM_NOT_SUPPORTED: /* TM rejected */
				lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
						 "0716 Task Mgmt Target "
						"reject\n");
				break;
			case RSP_TM_NOT_COMPLETED: /* TM failed */
				lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
						 "0717 Task Mgmt Target "
						"failed TM\n");
				break;
			case RSP_TM_INVALID_LU: /* TM to invalid LU! */
				lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
						 "0718 Task Mgmt to invalid "
						"LUN\n");
				break;
			}
		}
	}
	return ret;
}