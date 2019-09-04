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
struct icp_qat_fw_comn_req_hdr {int /*<<< orphan*/  serv_specif_flags; int /*<<< orphan*/  comn_req_flags; int /*<<< orphan*/  service_type; int /*<<< orphan*/  hdr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_QAT_FW_CIPH_IV_16BYTE_DATA ; 
 int /*<<< orphan*/  ICP_QAT_FW_COMN_FLAGS_BUILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_COMN_HDR_FLAGS_BUILD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_COMN_REQ_CPM_FW_LA ; 
 int /*<<< orphan*/  ICP_QAT_FW_COMN_REQ_FLAG_SET ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_CIPH_IV_FLD_FLAG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_NO_PROTO ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_NO_UPDATE_STATE ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_PARTIAL_NONE ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_PARTIAL_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_PROTO_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_UPDATE_STATE_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QAT_COMN_CD_FLD_TYPE_64BIT_ADR ; 
 int /*<<< orphan*/  QAT_COMN_PTR_TYPE_SGL ; 

__attribute__((used)) static void qat_alg_init_common_hdr(struct icp_qat_fw_comn_req_hdr *header)
{
	header->hdr_flags =
		ICP_QAT_FW_COMN_HDR_FLAGS_BUILD(ICP_QAT_FW_COMN_REQ_FLAG_SET);
	header->service_type = ICP_QAT_FW_COMN_REQ_CPM_FW_LA;
	header->comn_req_flags =
		ICP_QAT_FW_COMN_FLAGS_BUILD(QAT_COMN_CD_FLD_TYPE_64BIT_ADR,
					    QAT_COMN_PTR_TYPE_SGL);
	ICP_QAT_FW_LA_PARTIAL_SET(header->serv_specif_flags,
				  ICP_QAT_FW_LA_PARTIAL_NONE);
	ICP_QAT_FW_LA_CIPH_IV_FLD_FLAG_SET(header->serv_specif_flags,
					   ICP_QAT_FW_CIPH_IV_16BYTE_DATA);
	ICP_QAT_FW_LA_PROTO_SET(header->serv_specif_flags,
				ICP_QAT_FW_LA_NO_PROTO);
	ICP_QAT_FW_LA_UPDATE_STATE_SET(header->serv_specif_flags,
				       ICP_QAT_FW_LA_NO_UPDATE_STATE);
}