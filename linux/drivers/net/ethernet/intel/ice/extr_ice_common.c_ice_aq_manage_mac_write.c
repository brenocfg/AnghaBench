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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_manage_mac_write {int /*<<< orphan*/  sal; int /*<<< orphan*/  sah; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct ice_aqc_manage_mac_write mac_write; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/  const) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_manage_mac_write ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 

enum ice_status
ice_aq_manage_mac_write(struct ice_hw *hw, const u8 *mac_addr, u8 flags,
			struct ice_sq_cd *cd)
{
	struct ice_aqc_manage_mac_write *cmd;
	struct ice_aq_desc desc;

	cmd = &desc.params.mac_write;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_manage_mac_write);

	cmd->flags = flags;

	/* Prep values for flags, sah, sal */
	cmd->sah = htons(*((const u16 *)mac_addr));
	cmd->sal = htonl(*((const u32 *)(mac_addr + 2)));

	return ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
}