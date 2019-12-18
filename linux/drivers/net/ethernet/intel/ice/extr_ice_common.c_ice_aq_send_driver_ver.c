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
typedef  int u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_driver_ver {scalar_t__* driver_string; int /*<<< orphan*/  subbuild_ver; int /*<<< orphan*/  build_ver; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  major_ver; } ;
struct ice_aqc_driver_ver {int /*<<< orphan*/  subbuild_ver; int /*<<< orphan*/  build_ver; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  major_ver; } ;
struct TYPE_2__ {struct ice_aqc_driver_ver driver_ver; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,scalar_t__*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_driver_ver ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ isascii (scalar_t__) ; 

enum ice_status
ice_aq_send_driver_ver(struct ice_hw *hw, struct ice_driver_ver *dv,
		       struct ice_sq_cd *cd)
{
	struct ice_aqc_driver_ver *cmd;
	struct ice_aq_desc desc;
	u16 len;

	cmd = &desc.params.driver_ver;

	if (!dv)
		return ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_driver_ver);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	cmd->major_ver = dv->major_ver;
	cmd->minor_ver = dv->minor_ver;
	cmd->build_ver = dv->build_ver;
	cmd->subbuild_ver = dv->subbuild_ver;

	len = 0;
	while (len < sizeof(dv->driver_string) &&
	       isascii(dv->driver_string[len]) && dv->driver_string[len])
		len++;

	return ice_aq_send_cmd(hw, &desc, dv->driver_string, len, cd);
}