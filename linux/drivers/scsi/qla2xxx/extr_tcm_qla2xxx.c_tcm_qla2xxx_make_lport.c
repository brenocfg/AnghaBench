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
typedef  scalar_t__ u64 ;
struct se_wwn {int dummy; } ;
struct tcm_qla2xxx_lport {int /*<<< orphan*/  lport_fcport_map; int /*<<< orphan*/  lport_loopid_map; struct se_wwn lport_wwn; int /*<<< orphan*/  lport_naa_name; int /*<<< orphan*/ * lport_name; scalar_t__ lport_wwpn; } ;
struct target_fabric_configfs {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct se_wwn* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCM_QLA2XXX_NAMELEN ; 
 int /*<<< orphan*/  btree_destroy32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcm_qla2xxx_lport*) ; 
 struct tcm_qla2xxx_lport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qlt_lport_register (struct tcm_qla2xxx_lport*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  tcm_qla2xxx_format_wwn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int tcm_qla2xxx_init_lport (struct tcm_qla2xxx_lport*) ; 
 int /*<<< orphan*/  tcm_qla2xxx_lport_register_cb ; 
 scalar_t__ tcm_qla2xxx_parse_wwn (char const*,scalar_t__*,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct se_wwn *tcm_qla2xxx_make_lport(
	struct target_fabric_configfs *tf,
	struct config_group *group,
	const char *name)
{
	struct tcm_qla2xxx_lport *lport;
	u64 wwpn;
	int ret = -ENODEV;

	if (tcm_qla2xxx_parse_wwn(name, &wwpn, 1) < 0)
		return ERR_PTR(-EINVAL);

	lport = kzalloc(sizeof(struct tcm_qla2xxx_lport), GFP_KERNEL);
	if (!lport) {
		pr_err("Unable to allocate struct tcm_qla2xxx_lport\n");
		return ERR_PTR(-ENOMEM);
	}
	lport->lport_wwpn = wwpn;
	tcm_qla2xxx_format_wwn(&lport->lport_name[0], TCM_QLA2XXX_NAMELEN,
				wwpn);
	sprintf(lport->lport_naa_name, "naa.%016llx", (unsigned long long) wwpn);

	ret = tcm_qla2xxx_init_lport(lport);
	if (ret != 0)
		goto out;

	ret = qlt_lport_register(lport, wwpn, 0, 0,
				 tcm_qla2xxx_lport_register_cb);
	if (ret != 0)
		goto out_lport;

	return &lport->lport_wwn;
out_lport:
	vfree(lport->lport_loopid_map);
	btree_destroy32(&lport->lport_fcport_map);
out:
	kfree(lport);
	return ERR_PTR(ret);
}