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
struct iwl_trans {TYPE_1__* cfg; } ;
struct iwl_nvm_data {scalar_t__ nvm_version; scalar_t__ calib_version; } ;
struct TYPE_2__ {scalar_t__ nvm_ver; scalar_t__ nvm_calib_ver; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int iwl_nvm_check_version(struct iwl_nvm_data *data,
				 struct iwl_trans *trans)
{
	if (data->nvm_version >= trans->cfg->nvm_ver ||
	    data->calib_version >= trans->cfg->nvm_calib_ver) {
		IWL_DEBUG_INFO(trans, "device EEPROM VER=0x%x, CALIB=0x%x\n",
			       data->nvm_version, data->calib_version);
		return 0;
	}

	IWL_ERR(trans,
		"Unsupported (too old) EEPROM VER=0x%x < 0x%x CALIB=0x%x < 0x%x\n",
		data->nvm_version, trans->cfg->nvm_ver,
		data->calib_version,  trans->cfg->nvm_calib_ver);
	return -EINVAL;
}