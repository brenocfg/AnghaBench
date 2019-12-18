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
typedef  int u32 ;
struct iwl_fw_runtime {int dummy; } ;

/* Variables and functions */
 int EIO ; 
#define  FW_DBG_TRIGGER_ALIVE_TIMEOUT 131 
#define  FW_DBG_TRIGGER_DRIVER 130 
#define  FW_DBG_TRIGGER_FW_ASSERT 129 
#define  FW_DBG_TRIGGER_USER 128 
 int IWL_FW_TRIGGER_ID_FW_ASSERT ; 
 int IWL_FW_TRIGGER_ID_USER_TRIGGER ; 
 int _iwl_fw_dbg_ini_collect (struct iwl_fw_runtime*,int) ; 

int iwl_fw_dbg_ini_collect(struct iwl_fw_runtime *fwrt, u32 legacy_trigger_id)
{
	int id;

	switch (legacy_trigger_id) {
	case FW_DBG_TRIGGER_FW_ASSERT:
	case FW_DBG_TRIGGER_ALIVE_TIMEOUT:
	case FW_DBG_TRIGGER_DRIVER:
		id = IWL_FW_TRIGGER_ID_FW_ASSERT;
		break;
	case FW_DBG_TRIGGER_USER:
		id = IWL_FW_TRIGGER_ID_USER_TRIGGER;
		break;
	default:
		return -EIO;
	}

	return _iwl_fw_dbg_ini_collect(fwrt, id);
}