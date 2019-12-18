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
struct target_core_fabric_ops {int /*<<< orphan*/  fabric_name; int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  (* tpg_get_wwn ) (struct se_portal_group*) ;} ;
struct t10_pr_registration {char* pr_res_key; char* pr_reg_aptpl; int /*<<< orphan*/  pr_res_generation; scalar_t__ pr_reg_all_tg_pt; } ;
struct se_portal_group {int dummy; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; struct se_portal_group* se_tpg; } ;
struct se_device {TYPE_1__* transport; } ;
typedef  enum register_type { ____Placeholder_register_type } register_type ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int PR_REG_ISID_ID_LEN ; 
 int REGISTER_AND_IGNORE_EXISTING_KEY ; 
 int REGISTER_AND_MOVE ; 
 int /*<<< orphan*/  core_pr_dump_initiator_port (struct t10_pr_registration*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_portal_group*) ; 

__attribute__((used)) static void __core_scsi3_dump_registration(
	const struct target_core_fabric_ops *tfo,
	struct se_device *dev,
	struct se_node_acl *nacl,
	struct t10_pr_registration *pr_reg,
	enum register_type register_type)
{
	struct se_portal_group *se_tpg = nacl->se_tpg;
	char i_buf[PR_REG_ISID_ID_LEN];

	memset(&i_buf[0], 0, PR_REG_ISID_ID_LEN);
	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);

	pr_debug("SPC-3 PR [%s] Service Action: REGISTER%s Initiator"
		" Node: %s%s\n", tfo->fabric_name, (register_type == REGISTER_AND_MOVE) ?
		"_AND_MOVE" : (register_type == REGISTER_AND_IGNORE_EXISTING_KEY) ?
		"_AND_IGNORE_EXISTING_KEY" : "", nacl->initiatorname,
		i_buf);
	pr_debug("SPC-3 PR [%s] registration on Target Port: %s,0x%04x\n",
		 tfo->fabric_name, tfo->tpg_get_wwn(se_tpg),
		tfo->tpg_get_tag(se_tpg));
	pr_debug("SPC-3 PR [%s] for %s TCM Subsystem %s Object Target"
		" Port(s)\n",  tfo->fabric_name,
		(pr_reg->pr_reg_all_tg_pt) ? "ALL" : "SINGLE",
		dev->transport->name);
	pr_debug("SPC-3 PR [%s] SA Res Key: 0x%016Lx PRgeneration:"
		" 0x%08x  APTPL: %d\n", tfo->fabric_name,
		pr_reg->pr_res_key, pr_reg->pr_res_generation,
		pr_reg->pr_reg_aptpl);
}