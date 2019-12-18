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
struct iscsi_tpg_attrib {scalar_t__ default_cmdsn_depth; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; struct iscsi_tpg_attrib tpg_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TA_DEFAULT_CMDSN_DEPTH_MAX ; 
 scalar_t__ TA_DEFAULT_CMDSN_DEPTH_MIN ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 

int iscsit_ta_default_cmdsn_depth(
	struct iscsi_portal_group *tpg,
	u32 tcq_depth)
{
	struct iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	if (tcq_depth > TA_DEFAULT_CMDSN_DEPTH_MAX) {
		pr_err("Requested Default Queue Depth: %u larger"
			" than maximum %u\n", tcq_depth,
				TA_DEFAULT_CMDSN_DEPTH_MAX);
		return -EINVAL;
	} else if (tcq_depth < TA_DEFAULT_CMDSN_DEPTH_MIN) {
		pr_err("Requested Default Queue Depth: %u smaller"
			" than minimum %u\n", tcq_depth,
				TA_DEFAULT_CMDSN_DEPTH_MIN);
		return -EINVAL;
	}

	a->default_cmdsn_depth = tcq_depth;
	pr_debug("iSCSI_TPG[%hu] - Set Default CmdSN TCQ Depth to %u\n",
		tpg->tpgt, a->default_cmdsn_depth);

	return 0;
}