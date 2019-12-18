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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_3__ {int split_type; scalar_t__ split_id; } ;
struct dbg_tools_data {scalar_t__ num_regs_read; size_t platform_id; scalar_t__ num_pfs_per_port; scalar_t__ num_ports; TYPE_1__ pretend; scalar_t__ use_dmae; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum init_split_types { ____Placeholder_init_split_types } init_split_types ;
struct TYPE_4__ {scalar_t__ log_thresh; scalar_t__ dmae_thresh; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWORDS_TO_BYTES (scalar_t__) ; 
 scalar_t__ PXP_PRETEND_CONCRETE_FID_PFID_SHIFT ; 
 scalar_t__ PXP_PRETEND_CONCRETE_FID_VFID_SHIFT ; 
 int /*<<< orphan*/  PXP_PRETEND_CONCRETE_FID_VFVALID_SHIFT ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int SPLIT_TYPE_NONE ; 
#define  SPLIT_TYPE_PF 131 
#define  SPLIT_TYPE_PORT 130 
#define  SPLIT_TYPE_PORT_PF 129 
#define  SPLIT_TYPE_VF 128 
 int /*<<< orphan*/  qed_dmae_grc2host (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_fid_pretend (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_port_fid_pretend (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qed_port_pretend (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_read_regs (struct qed_hwfn*,struct qed_ptt*,scalar_t__*,scalar_t__,scalar_t__) ; 
 TYPE_2__* s_platform_defs ; 

__attribute__((used)) static u32 qed_grc_dump_addr_range(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt,
				   u32 *dump_buf,
				   bool dump, u32 addr, u32 len, bool wide_bus,
				   enum init_split_types split_type,
				   u8 split_id)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 port_id = 0, pf_id = 0, vf_id = 0, fid = 0;

	if (!dump)
		return len;

	/* Print log if needed */
	dev_data->num_regs_read += len;
	if (dev_data->num_regs_read >=
	    s_platform_defs[dev_data->platform_id].log_thresh) {
		DP_VERBOSE(p_hwfn,
			   QED_MSG_DEBUG,
			   "Dumping %d registers...\n",
			   dev_data->num_regs_read);
		dev_data->num_regs_read = 0;
	}

	switch (split_type) {
	case SPLIT_TYPE_PORT:
		port_id = split_id;
		break;
	case SPLIT_TYPE_PF:
		pf_id = split_id;
		break;
	case SPLIT_TYPE_PORT_PF:
		port_id = split_id / dev_data->num_pfs_per_port;
		pf_id = port_id + dev_data->num_ports *
		    (split_id % dev_data->num_pfs_per_port);
		break;
	case SPLIT_TYPE_VF:
		vf_id = split_id;
		break;
	default:
		break;
	}

	/* Try reading using DMAE */
	if (dev_data->use_dmae && split_type == SPLIT_TYPE_NONE &&
	    (len >= s_platform_defs[dev_data->platform_id].dmae_thresh ||
	     wide_bus)) {
		if (!qed_dmae_grc2host(p_hwfn, p_ptt, DWORDS_TO_BYTES(addr),
				       (u64)(uintptr_t)(dump_buf), len, NULL))
			return len;
		dev_data->use_dmae = 0;
		DP_VERBOSE(p_hwfn,
			   QED_MSG_DEBUG,
			   "Failed reading from chip using DMAE, using GRC instead\n");
	}

	/* If not read using DMAE, read using GRC */

	/* Set pretend */
	if (split_type != dev_data->pretend.split_type || split_id !=
	    dev_data->pretend.split_id) {
		switch (split_type) {
		case SPLIT_TYPE_PORT:
			qed_port_pretend(p_hwfn, p_ptt, port_id);
			break;
		case SPLIT_TYPE_PF:
			fid = pf_id << PXP_PRETEND_CONCRETE_FID_PFID_SHIFT;
			qed_fid_pretend(p_hwfn, p_ptt, fid);
			break;
		case SPLIT_TYPE_PORT_PF:
			fid = pf_id << PXP_PRETEND_CONCRETE_FID_PFID_SHIFT;
			qed_port_fid_pretend(p_hwfn, p_ptt, port_id, fid);
			break;
		case SPLIT_TYPE_VF:
			fid = BIT(PXP_PRETEND_CONCRETE_FID_VFVALID_SHIFT) |
			      (vf_id << PXP_PRETEND_CONCRETE_FID_VFID_SHIFT);
			qed_fid_pretend(p_hwfn, p_ptt, fid);
			break;
		default:
			break;
		}

		dev_data->pretend.split_type = (u8)split_type;
		dev_data->pretend.split_id = split_id;
	}

	/* Read registers using GRC */
	qed_read_regs(p_hwfn, p_ptt, dump_buf, addr, len);

	return len;
}