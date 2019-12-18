#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {int serial0; int serial2; int serial1; char* model_number; char* model_desc; char* adapter_id; char* bios_revision; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_7__* isp_ops; TYPE_13__* ct_sns; } ;
struct TYPE_25__ {int /*<<< orphan*/  explanation_code; int /*<<< orphan*/  reason_code; } ;
struct ct_sns_rsp {TYPE_6__ header; } ;
struct TYPE_21__ {void* count; } ;
struct TYPE_23__ {int /*<<< orphan*/  hba_identifier; TYPE_2__ attrs; int /*<<< orphan*/  port_name; void* entry_count; } ;
struct TYPE_24__ {TYPE_4__ rhba; } ;
struct ct_sns_req {TYPE_5__ req; } ;
struct TYPE_22__ {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  orom_version; int /*<<< orphan*/  driver_version; int /*<<< orphan*/  hw_version; int /*<<< orphan*/  model_desc; int /*<<< orphan*/  model; int /*<<< orphan*/  serial_num; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  node_name; } ;
struct ct_fdmi_hba_attr {TYPE_3__ a; void* len; void* type; } ;
struct TYPE_27__ {int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; struct qla_hw_data* hw; } ;
typedef  TYPE_8__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_26__ {int /*<<< orphan*/  (* fw_version_str ) (TYPE_8__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/ * (* prep_ms_fdmi_iocb ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {struct ct_sns_rsp rsp; } ;
struct TYPE_19__ {TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_EXPL_ALREADY_REGISTERED ; 
 int /*<<< orphan*/  CT_REASON_CANNOT_PERFORM ; 
 int FDMI_HBA_ATTR_COUNT ; 
 int FDMI_HBA_DRIVER_VERSION ; 
 int FDMI_HBA_FIRMWARE_VERSION ; 
 int FDMI_HBA_HARDWARE_VERSION ; 
 int FDMI_HBA_MANUFACTURER ; 
 int FDMI_HBA_MODEL ; 
 int FDMI_HBA_MODEL_DESCRIPTION ; 
 int FDMI_HBA_NODE_NAME ; 
 int FDMI_HBA_OPTION_ROM_VERSION ; 
 int FDMI_HBA_SERIAL_NUMBER ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLA2XXX_MANUFACTURER ; 
 int QLA_ALREADY_REGISTERED ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RHBA_CMD ; 
 int /*<<< orphan*/  RHBA_RSP_SIZE ; 
 int WWN_SIZE ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_8__*,int,char*,...) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_8__*,int,void*,int) ; 
 int qla2x00_chk_ms_status (TYPE_8__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 int qla2x00_issue_iocb (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_fdmi_req (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_update_ms_fdmi_iocb (TYPE_8__*,int) ; 
 char* qla2x00_version_str ; 
 scalar_t__ qla2xxx_get_vpd_field (TYPE_8__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qla2x00_fdmi_rhba(scsi_qla_host_t *vha)
{
	int rval, alen;
	uint32_t size, sn;

	ms_iocb_entry_t *ms_pkt;
	struct ct_sns_req *ct_req;
	struct ct_sns_rsp *ct_rsp;
	void *entries;
	struct ct_fdmi_hba_attr *eiter;
	struct qla_hw_data *ha = vha->hw;

	/* Issue RHBA */
	/* Prepare common MS IOCB */
	/*   Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, 0, RHBA_RSP_SIZE);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(ha->ct_sns, RHBA_CMD, RHBA_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare FDMI command arguments -- attribute block, attributes. */
	memcpy(ct_req->req.rhba.hba_identifier, vha->port_name, WWN_SIZE);
	ct_req->req.rhba.entry_count = cpu_to_be32(1);
	memcpy(ct_req->req.rhba.port_name, vha->port_name, WWN_SIZE);
	size = 2 * WWN_SIZE + 4 + 4;

	/* Attributes */
	ct_req->req.rhba.attrs.count =
	    cpu_to_be32(FDMI_HBA_ATTR_COUNT);
	entries = &ct_req->req;

	/* Nodename. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_NODE_NAME);
	eiter->len = cpu_to_be16(4 + WWN_SIZE);
	memcpy(eiter->a.node_name, vha->node_name, WWN_SIZE);
	size += 4 + WWN_SIZE;

	ql_dbg(ql_dbg_disc, vha, 0x2025,
	    "NodeName = %8phN.\n", eiter->a.node_name);

	/* Manufacturer. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MANUFACTURER);
	alen = strlen(QLA2XXX_MANUFACTURER);
	snprintf(eiter->a.manufacturer, sizeof(eiter->a.manufacturer),
	    "%s", "QLogic Corporation");
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x2026,
	    "Manufacturer = %s.\n", eiter->a.manufacturer);

	/* Serial number. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_SERIAL_NUMBER);
	if (IS_FWI2_CAPABLE(ha))
		qla2xxx_get_vpd_field(vha, "SN", eiter->a.serial_num,
		    sizeof(eiter->a.serial_num));
	else {
		sn = ((ha->serial0 & 0x1f) << 16) |
			(ha->serial2 << 8) | ha->serial1;
		snprintf(eiter->a.serial_num, sizeof(eiter->a.serial_num),
		    "%c%05d", 'A' + sn / 100000, sn % 100000);
	}
	alen = strlen(eiter->a.serial_num);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x2027,
	    "Serial no. = %s.\n", eiter->a.serial_num);

	/* Model name. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MODEL);
	snprintf(eiter->a.model, sizeof(eiter->a.model),
	    "%s", ha->model_number);
	alen = strlen(eiter->a.model);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x2028,
	    "Model Name = %s.\n", eiter->a.model);

	/* Model description. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MODEL_DESCRIPTION);
	snprintf(eiter->a.model_desc, sizeof(eiter->a.model_desc),
	    "%s", ha->model_desc);
	alen = strlen(eiter->a.model_desc);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x2029,
	    "Model Desc = %s.\n", eiter->a.model_desc);

	/* Hardware version. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_HARDWARE_VERSION);
	if (!IS_FWI2_CAPABLE(ha)) {
		snprintf(eiter->a.hw_version, sizeof(eiter->a.hw_version),
		    "HW:%s", ha->adapter_id);
	} else if (qla2xxx_get_vpd_field(vha, "MN", eiter->a.hw_version,
		    sizeof(eiter->a.hw_version))) {
		;
	} else if (qla2xxx_get_vpd_field(vha, "EC", eiter->a.hw_version,
		    sizeof(eiter->a.hw_version))) {
		;
	} else {
		snprintf(eiter->a.hw_version, sizeof(eiter->a.hw_version),
		    "HW:%s", ha->adapter_id);
	}
	alen = strlen(eiter->a.hw_version);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x202a,
	    "Hardware ver = %s.\n", eiter->a.hw_version);

	/* Driver version. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_DRIVER_VERSION);
	snprintf(eiter->a.driver_version, sizeof(eiter->a.driver_version),
	    "%s", qla2x00_version_str);
	alen = strlen(eiter->a.driver_version);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x202b,
	    "Driver ver = %s.\n", eiter->a.driver_version);

	/* Option ROM version. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_OPTION_ROM_VERSION);
	snprintf(eiter->a.orom_version, sizeof(eiter->a.orom_version),
	    "%d.%02d", ha->bios_revision[1], ha->bios_revision[0]);
	alen = strlen(eiter->a.orom_version);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha , 0x202c,
	    "Optrom vers = %s.\n", eiter->a.orom_version);

	/* Firmware version */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_FIRMWARE_VERSION);
	ha->isp_ops->fw_version_str(vha, eiter->a.fw_version,
	    sizeof(eiter->a.fw_version));
	alen = strlen(eiter->a.fw_version);
	alen += 4 - (alen & 3);
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x202d,
	    "Firmware vers = %s.\n", eiter->a.fw_version);

	/* Update MS request size. */
	qla2x00_update_ms_fdmi_iocb(vha, size + 16);

	ql_dbg(ql_dbg_disc, vha, 0x202e,
	    "RHBA identifier = %8phN size=%d.\n",
	    ct_req->req.rhba.hba_identifier, size);
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x2076,
	    entries, size);

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2030,
		    "RHBA issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RHBA") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
		if (ct_rsp->header.reason_code == CT_REASON_CANNOT_PERFORM &&
		    ct_rsp->header.explanation_code ==
		    CT_EXPL_ALREADY_REGISTERED) {
			ql_dbg(ql_dbg_disc, vha, 0x2034,
			    "HBA already registered.\n");
			rval = QLA_ALREADY_REGISTERED;
		} else {
			ql_dbg(ql_dbg_disc, vha, 0x20ad,
			    "RHBA FDMI registration failed, CT Reason code: 0x%x, CT Explanation 0x%x\n",
			    ct_rsp->header.reason_code,
			    ct_rsp->header.explanation_code);
		}
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2035,
		    "RHBA exiting normally.\n");
	}

	return rval;
}