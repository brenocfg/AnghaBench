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
typedef  scalar_t__ u32 ;
struct swchnlcmd {int cmdid; scalar_t__ msdelay; scalar_t__ para2; scalar_t__ para1; } ;
typedef  enum swchnlcmd_id { ____Placeholder_swchnlcmd_id } swchnlcmd_id ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

__attribute__((used)) static bool _rtl92d_phy_set_sw_chnl_cmdarray(struct swchnlcmd *cmdtable,
		u32 cmdtableidx, u32 cmdtablesz, enum swchnlcmd_id cmdid,
		u32 para1, u32 para2, u32 msdelay)
{
	struct swchnlcmd *pcmd;

	if (cmdtable == NULL) {
		WARN_ONCE(true, "rtl8192de: cmdtable cannot be NULL\n");
		return false;
	}
	if (cmdtableidx >= cmdtablesz)
		return false;

	pcmd = cmdtable + cmdtableidx;
	pcmd->cmdid = cmdid;
	pcmd->para1 = para1;
	pcmd->para2 = para2;
	pcmd->msdelay = msdelay;
	return true;
}