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
typedef  scalar_t__ u32 ;
struct iwl_ucode_tlv {int /*<<< orphan*/  type; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int external_ini_cfg; int internal_ini_cfg; } ;
struct iwl_trans {TYPE_1__ dbg; } ;
struct iwl_fw_ini_header {int /*<<< orphan*/  tlv_version; int /*<<< orphan*/  apply_point; } ;
typedef  enum iwl_ini_cfg_state { ____Placeholder_iwl_ini_cfg_state } iwl_ini_cfg_state ;

/* Variables and functions */
 scalar_t__ IWL_DBG_TLV_TYPE_NUM ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_trans*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,scalar_t__,...) ; 
 int IWL_INI_CFG_STATE_CORRUPTED ; 
 int IWL_INI_CFG_STATE_LOADED ; 
 int IWL_INI_CFG_STATE_NOT_LOADED ; 
 scalar_t__ IWL_UCODE_TLV_DEBUG_BASE ; 
 int /*<<< orphan*/  iwl_dbg_tlv_ver_support (struct iwl_ucode_tlv*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

void iwl_dbg_tlv_alloc(struct iwl_trans *trans, struct iwl_ucode_tlv *tlv,
		       bool ext)
{
	struct iwl_fw_ini_header *hdr = (void *)&tlv->data[0];
	u32 type = le32_to_cpu(tlv->type);
	u32 pnt = le32_to_cpu(hdr->apply_point);
	u32 tlv_idx = type - IWL_UCODE_TLV_DEBUG_BASE;
	enum iwl_ini_cfg_state *cfg_state = ext ?
		&trans->dbg.external_ini_cfg : &trans->dbg.internal_ini_cfg;

	IWL_DEBUG_FW(trans, "WRT: read TLV 0x%x, apply point %d\n",
		     type, pnt);

	if (tlv_idx >= IWL_DBG_TLV_TYPE_NUM) {
		IWL_ERR(trans, "WRT: Unsupported TLV 0x%x\n", type);
		goto out_err;
	}

	if (!iwl_dbg_tlv_ver_support(tlv)) {
		IWL_ERR(trans, "WRT: Unsupported TLV 0x%x version %u\n", type,
			le32_to_cpu(hdr->tlv_version));
		goto out_err;
	}

	if (*cfg_state == IWL_INI_CFG_STATE_NOT_LOADED)
		*cfg_state = IWL_INI_CFG_STATE_LOADED;

	return;

out_err:
	*cfg_state = IWL_INI_CFG_STATE_CORRUPTED;
}