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
struct iscsi_tpg_attrib {int fabric_prot_type; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; struct iscsi_tpg_attrib tpg_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int iscsit_ta_fabric_prot_type(
	struct iscsi_portal_group *tpg,
	u32 prot_type)
{
	struct iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	if ((prot_type != 0) && (prot_type != 1) && (prot_type != 3)) {
		pr_err("Illegal value for fabric_prot_type: %u\n", prot_type);
		return -EINVAL;
	}

	a->fabric_prot_type = prot_type;
	pr_debug("iSCSI_TPG[%hu] - T10 Fabric Protection Type: %u\n",
		 tpg->tpgt, prot_type);

	return 0;
}