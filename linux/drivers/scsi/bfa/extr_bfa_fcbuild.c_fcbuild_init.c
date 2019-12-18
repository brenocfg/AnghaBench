#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {int seq_id; void* rx_id; void* f_ctl; void* type; int /*<<< orphan*/  cat_info; int /*<<< orphan*/  routing; } ;
struct TYPE_21__ {int class_valid; int sequential; int conseq; int ospx; } ;
struct TYPE_20__ {int ciro; int cisc; int altbbcred; int /*<<< orphan*/  e_d_tov; void* ro_bitmap; void* conseq; int /*<<< orphan*/  verlo; int /*<<< orphan*/  verhi; } ;
struct TYPE_27__ {TYPE_2__ class3; TYPE_1__ csp; } ;
struct TYPE_22__ {int rxrdisab; } ;
struct TYPE_23__ {int imagepair; TYPE_3__ servparams; void* type; } ;
struct TYPE_26__ {int pglen; TYPE_4__ parampage; void* pagebytes; int /*<<< orphan*/  command; } ;
struct TYPE_24__ {int /*<<< orphan*/  els_code; } ;
struct TYPE_25__ {TYPE_5__ els_cmd; } ;
struct TYPE_19__ {int high_seq_cnt; scalar_t__ low_seq_cnt; scalar_t__ seq_id_valid; } ;
struct TYPE_18__ {void* rx_id; void* f_ctl; void* type; void* routing; } ;
struct TYPE_17__ {void* rx_id; void* f_ctl; void* type; int /*<<< orphan*/  cat_info; void* routing; } ;
struct TYPE_16__ {void* rx_id; void* f_ctl; void* type; int /*<<< orphan*/  cat_info; void* routing; } ;
struct TYPE_15__ {void* rx_id; void* f_ctl; void* type; int /*<<< orphan*/  cat_info; void* routing; } ;

/* Variables and functions */
 int FCTL_EC_RESP ; 
 int FCTL_END_SEQ ; 
 int FCTL_FS_EXCH ; 
 int FCTL_LS_EXCH ; 
 int FCTL_SEQ_INI ; 
 int FCTL_SI_XFER ; 
 int /*<<< orphan*/  FC_CAT_BA_ACC ; 
 int /*<<< orphan*/  FC_CAT_LD_REPLY ; 
 int /*<<< orphan*/  FC_CAT_LD_REQUEST ; 
 int /*<<< orphan*/  FC_CAT_UNSOLICIT_CMD ; 
 int /*<<< orphan*/  FC_ELS_PRLI ; 
 int /*<<< orphan*/  FC_ELS_RRQ ; 
 int /*<<< orphan*/  FC_PH_VER_4_3 ; 
 int /*<<< orphan*/  FC_PH_VER_PH_3 ; 
 void* FC_RTG_BASIC_LINK ; 
 void* FC_RTG_EXT_LINK ; 
 int /*<<< orphan*/  FC_RTG_FC4_DEV_DATA ; 
 void* FC_RXID_ANY ; 
 void* FC_TYPE_BLS ; 
 void* FC_TYPE_ELS ; 
 void* FC_TYPE_FCP ; 
 TYPE_14__ ba_acc_tmpl ; 
 void* bfa_hton3b (int) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 TYPE_13__ fc_bls_req_tmpl ; 
 TYPE_12__ fc_bls_rsp_tmpl ; 
 TYPE_11__ fc_els_req_tmpl ; 
 TYPE_10__ fc_els_rsp_tmpl ; 
 TYPE_9__ fcp_fchs_tmpl ; 
 TYPE_8__ plogi_tmpl ; 
 TYPE_7__ prli_tmpl ; 
 TYPE_6__ rrq_tmpl ; 

void
fcbuild_init(void)
{
	/*
	 * fc_els_req_tmpl
	 */
	fc_els_req_tmpl.routing = FC_RTG_EXT_LINK;
	fc_els_req_tmpl.cat_info = FC_CAT_LD_REQUEST;
	fc_els_req_tmpl.type = FC_TYPE_ELS;
	fc_els_req_tmpl.f_ctl =
		bfa_hton3b(FCTL_SEQ_INI | FCTL_FS_EXCH | FCTL_END_SEQ |
			      FCTL_SI_XFER);
	fc_els_req_tmpl.rx_id = FC_RXID_ANY;

	/*
	 * fc_els_rsp_tmpl
	 */
	fc_els_rsp_tmpl.routing = FC_RTG_EXT_LINK;
	fc_els_rsp_tmpl.cat_info = FC_CAT_LD_REPLY;
	fc_els_rsp_tmpl.type = FC_TYPE_ELS;
	fc_els_rsp_tmpl.f_ctl =
		bfa_hton3b(FCTL_EC_RESP | FCTL_SEQ_INI | FCTL_LS_EXCH |
			      FCTL_END_SEQ | FCTL_SI_XFER);
	fc_els_rsp_tmpl.rx_id = FC_RXID_ANY;

	/*
	 * fc_bls_req_tmpl
	 */
	fc_bls_req_tmpl.routing = FC_RTG_BASIC_LINK;
	fc_bls_req_tmpl.type = FC_TYPE_BLS;
	fc_bls_req_tmpl.f_ctl = bfa_hton3b(FCTL_END_SEQ | FCTL_SI_XFER);
	fc_bls_req_tmpl.rx_id = FC_RXID_ANY;

	/*
	 * fc_bls_rsp_tmpl
	 */
	fc_bls_rsp_tmpl.routing = FC_RTG_BASIC_LINK;
	fc_bls_rsp_tmpl.cat_info = FC_CAT_BA_ACC;
	fc_bls_rsp_tmpl.type = FC_TYPE_BLS;
	fc_bls_rsp_tmpl.f_ctl =
		bfa_hton3b(FCTL_EC_RESP | FCTL_SEQ_INI | FCTL_LS_EXCH |
			      FCTL_END_SEQ | FCTL_SI_XFER);
	fc_bls_rsp_tmpl.rx_id = FC_RXID_ANY;

	/*
	 * ba_acc_tmpl
	 */
	ba_acc_tmpl.seq_id_valid = 0;
	ba_acc_tmpl.low_seq_cnt = 0;
	ba_acc_tmpl.high_seq_cnt = 0xFFFF;

	/*
	 * plogi_tmpl
	 */
	plogi_tmpl.csp.verhi = FC_PH_VER_PH_3;
	plogi_tmpl.csp.verlo = FC_PH_VER_4_3;
	plogi_tmpl.csp.ciro = 0x1;
	plogi_tmpl.csp.cisc = 0x0;
	plogi_tmpl.csp.altbbcred = 0x0;
	plogi_tmpl.csp.conseq = cpu_to_be16(0x00FF);
	plogi_tmpl.csp.ro_bitmap = cpu_to_be16(0x0002);
	plogi_tmpl.csp.e_d_tov = cpu_to_be32(2000);

	plogi_tmpl.class3.class_valid = 1;
	plogi_tmpl.class3.sequential = 1;
	plogi_tmpl.class3.conseq = 0xFF;
	plogi_tmpl.class3.ospx = 1;

	/*
	 * prli_tmpl
	 */
	prli_tmpl.command = FC_ELS_PRLI;
	prli_tmpl.pglen = 0x10;
	prli_tmpl.pagebytes = cpu_to_be16(0x0014);
	prli_tmpl.parampage.type = FC_TYPE_FCP;
	prli_tmpl.parampage.imagepair = 1;
	prli_tmpl.parampage.servparams.rxrdisab = 1;

	/*
	 * rrq_tmpl
	 */
	rrq_tmpl.els_cmd.els_code = FC_ELS_RRQ;

	/*
	 * fcp_struct fchs_s mpl
	 */
	fcp_fchs_tmpl.routing = FC_RTG_FC4_DEV_DATA;
	fcp_fchs_tmpl.cat_info = FC_CAT_UNSOLICIT_CMD;
	fcp_fchs_tmpl.type = FC_TYPE_FCP;
	fcp_fchs_tmpl.f_ctl =
		bfa_hton3b(FCTL_FS_EXCH | FCTL_END_SEQ | FCTL_SI_XFER);
	fcp_fchs_tmpl.seq_id = 1;
	fcp_fchs_tmpl.rx_id = FC_RXID_ANY;
}