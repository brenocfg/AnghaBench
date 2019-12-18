#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wqe_com; } ;
struct TYPE_5__ {int /*<<< orphan*/  wqe_com; } ;
struct TYPE_4__ {int /*<<< orphan*/  wqe_com; } ;
union lpfc_wqe128 {TYPE_3__ fcp_icmd; TYPE_2__ fcp_iwrite; TYPE_1__ fcp_iread; } ;

/* Variables and functions */
 int CLASS3 ; 
 int CMD_FCP_ICMND64_WQE ; 
 int CMD_FCP_IREAD64_WQE ; 
 int CMD_FCP_IWRITE64_WQE ; 
 int FCP_COMMAND ; 
 int LPFC_WQE_CQ_ID_DEFAULT ; 
 int LPFC_WQE_IOD_NONE ; 
 int LPFC_WQE_IOD_READ ; 
 int LPFC_WQE_IOD_WRITE ; 
 int LPFC_WQE_LENLOC_NONE ; 
 int LPFC_WQE_LENLOC_WORD4 ; 
 int NVME_READ_CMD ; 
 int NVME_WRITE_CMD ; 
 int PARM_READ_CHECK ; 
 int SLI4_CT_RPI ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 union lpfc_wqe128 lpfc_icmnd_cmd_template ; 
 union lpfc_wqe128 lpfc_iread_cmd_template ; 
 union lpfc_wqe128 lpfc_iwrite_cmd_template ; 
 int /*<<< orphan*/  memset (union lpfc_wqe128*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wqe_class ; 
 int /*<<< orphan*/  wqe_cmd_type ; 
 int /*<<< orphan*/  wqe_cmnd ; 
 int /*<<< orphan*/  wqe_cqid ; 
 int /*<<< orphan*/  wqe_ct ; 
 int /*<<< orphan*/  wqe_dbde ; 
 int /*<<< orphan*/  wqe_iod ; 
 int /*<<< orphan*/  wqe_lenloc ; 
 int /*<<< orphan*/  wqe_nvme ; 
 int /*<<< orphan*/  wqe_pbde ; 
 int /*<<< orphan*/  wqe_pu ; 
 int /*<<< orphan*/  wqe_qosd ; 
 int /*<<< orphan*/  wqe_wqes ; 

void
lpfc_nvme_cmd_template(void)
{
	union lpfc_wqe128 *wqe;

	/* IREAD template */
	wqe = &lpfc_iread_cmd_template;
	memset(wqe, 0, sizeof(union lpfc_wqe128));

	/* Word 0, 1, 2 - BDE is variable */

	/* Word 3 - cmd_buff_len, payload_offset_len is zero */

	/* Word 4 - total_xfer_len is variable */

	/* Word 5 - is zero */

	/* Word 6 - ctxt_tag, xri_tag is variable */

	/* Word 7 */
	bf_set(wqe_cmnd, &wqe->fcp_iread.wqe_com, CMD_FCP_IREAD64_WQE);
	bf_set(wqe_pu, &wqe->fcp_iread.wqe_com, PARM_READ_CHECK);
	bf_set(wqe_class, &wqe->fcp_iread.wqe_com, CLASS3);
	bf_set(wqe_ct, &wqe->fcp_iread.wqe_com, SLI4_CT_RPI);

	/* Word 8 - abort_tag is variable */

	/* Word 9  - reqtag is variable */

	/* Word 10 - dbde, wqes is variable */
	bf_set(wqe_qosd, &wqe->fcp_iread.wqe_com, 0);
	bf_set(wqe_nvme, &wqe->fcp_iread.wqe_com, 1);
	bf_set(wqe_iod, &wqe->fcp_iread.wqe_com, LPFC_WQE_IOD_READ);
	bf_set(wqe_lenloc, &wqe->fcp_iread.wqe_com, LPFC_WQE_LENLOC_WORD4);
	bf_set(wqe_dbde, &wqe->fcp_iread.wqe_com, 0);
	bf_set(wqe_wqes, &wqe->fcp_iread.wqe_com, 1);

	/* Word 11 - pbde is variable */
	bf_set(wqe_cmd_type, &wqe->fcp_iread.wqe_com, NVME_READ_CMD);
	bf_set(wqe_cqid, &wqe->fcp_iread.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_pbde, &wqe->fcp_iread.wqe_com, 1);

	/* Word 12 - is zero */

	/* Word 13, 14, 15 - PBDE is variable */

	/* IWRITE template */
	wqe = &lpfc_iwrite_cmd_template;
	memset(wqe, 0, sizeof(union lpfc_wqe128));

	/* Word 0, 1, 2 - BDE is variable */

	/* Word 3 - cmd_buff_len, payload_offset_len is zero */

	/* Word 4 - total_xfer_len is variable */

	/* Word 5 - initial_xfer_len is variable */

	/* Word 6 - ctxt_tag, xri_tag is variable */

	/* Word 7 */
	bf_set(wqe_cmnd, &wqe->fcp_iwrite.wqe_com, CMD_FCP_IWRITE64_WQE);
	bf_set(wqe_pu, &wqe->fcp_iwrite.wqe_com, PARM_READ_CHECK);
	bf_set(wqe_class, &wqe->fcp_iwrite.wqe_com, CLASS3);
	bf_set(wqe_ct, &wqe->fcp_iwrite.wqe_com, SLI4_CT_RPI);

	/* Word 8 - abort_tag is variable */

	/* Word 9  - reqtag is variable */

	/* Word 10 - dbde, wqes is variable */
	bf_set(wqe_qosd, &wqe->fcp_iwrite.wqe_com, 0);
	bf_set(wqe_nvme, &wqe->fcp_iwrite.wqe_com, 1);
	bf_set(wqe_iod, &wqe->fcp_iwrite.wqe_com, LPFC_WQE_IOD_WRITE);
	bf_set(wqe_lenloc, &wqe->fcp_iwrite.wqe_com, LPFC_WQE_LENLOC_WORD4);
	bf_set(wqe_dbde, &wqe->fcp_iwrite.wqe_com, 0);
	bf_set(wqe_wqes, &wqe->fcp_iwrite.wqe_com, 1);

	/* Word 11 - pbde is variable */
	bf_set(wqe_cmd_type, &wqe->fcp_iwrite.wqe_com, NVME_WRITE_CMD);
	bf_set(wqe_cqid, &wqe->fcp_iwrite.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_pbde, &wqe->fcp_iwrite.wqe_com, 1);

	/* Word 12 - is zero */

	/* Word 13, 14, 15 - PBDE is variable */

	/* ICMND template */
	wqe = &lpfc_icmnd_cmd_template;
	memset(wqe, 0, sizeof(union lpfc_wqe128));

	/* Word 0, 1, 2 - BDE is variable */

	/* Word 3 - payload_offset_len is variable */

	/* Word 4, 5 - is zero */

	/* Word 6 - ctxt_tag, xri_tag is variable */

	/* Word 7 */
	bf_set(wqe_cmnd, &wqe->fcp_icmd.wqe_com, CMD_FCP_ICMND64_WQE);
	bf_set(wqe_pu, &wqe->fcp_icmd.wqe_com, 0);
	bf_set(wqe_class, &wqe->fcp_icmd.wqe_com, CLASS3);
	bf_set(wqe_ct, &wqe->fcp_icmd.wqe_com, SLI4_CT_RPI);

	/* Word 8 - abort_tag is variable */

	/* Word 9  - reqtag is variable */

	/* Word 10 - dbde, wqes is variable */
	bf_set(wqe_qosd, &wqe->fcp_icmd.wqe_com, 1);
	bf_set(wqe_nvme, &wqe->fcp_icmd.wqe_com, 1);
	bf_set(wqe_iod, &wqe->fcp_icmd.wqe_com, LPFC_WQE_IOD_NONE);
	bf_set(wqe_lenloc, &wqe->fcp_icmd.wqe_com, LPFC_WQE_LENLOC_NONE);
	bf_set(wqe_dbde, &wqe->fcp_icmd.wqe_com, 0);
	bf_set(wqe_wqes, &wqe->fcp_icmd.wqe_com, 1);

	/* Word 11 */
	bf_set(wqe_cmd_type, &wqe->fcp_icmd.wqe_com, FCP_COMMAND);
	bf_set(wqe_cqid, &wqe->fcp_icmd.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_pbde, &wqe->fcp_icmd.wqe_com, 0);

	/* Word 12, 13, 14, 15 - is zero */
}