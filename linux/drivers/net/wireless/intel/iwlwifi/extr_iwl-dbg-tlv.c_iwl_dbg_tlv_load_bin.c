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
struct iwl_trans {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_ini; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_dbg_tlv_parse_bin (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,struct device*) ; 

void iwl_dbg_tlv_load_bin(struct device *dev, struct iwl_trans *trans)
{
	const struct firmware *fw;
	int res;

	if (!iwlwifi_mod_params.enable_ini)
		return;

	res = request_firmware(&fw, "iwl-dbg-tlv.ini", dev);
	if (res)
		return;

	iwl_dbg_tlv_parse_bin(trans, fw->data, fw->size);

	release_firmware(fw);
}