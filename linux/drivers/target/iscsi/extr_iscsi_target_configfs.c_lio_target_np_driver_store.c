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
struct iscsi_tpg_np {struct iscsi_portal_group* tpg; struct iscsi_np* tpg_np; } ;
struct iscsi_portal_group {int dummy; } ;
struct iscsi_np {int /*<<< orphan*/  np_sockaddr; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
typedef  enum iscsit_transport_type { ____Placeholder_iscsit_transport_type } iscsit_transport_type ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct iscsi_tpg_np*) ; 
 int PTR_ERR (struct iscsi_tpg_np*) ; 
 scalar_t__ iscsit_get_tpg (struct iscsi_portal_group*) ; 
 int /*<<< orphan*/  iscsit_put_tpg (struct iscsi_portal_group*) ; 
 struct iscsi_tpg_np* iscsit_tpg_add_network_portal (struct iscsi_portal_group*,int /*<<< orphan*/ *,struct iscsi_tpg_np*,int) ; 
 int iscsit_tpg_del_network_portal (struct iscsi_portal_group*,struct iscsi_tpg_np*) ; 
 struct iscsi_tpg_np* iscsit_tpg_locate_child_np (struct iscsi_tpg_np*,int) ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 int request_module (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 struct iscsi_tpg_np* to_iscsi_tpg_np (struct config_item*) ; 

__attribute__((used)) static ssize_t lio_target_np_driver_store(struct config_item *item,
		const char *page, size_t count, enum iscsit_transport_type type,
		const char *mod_name)
{
	struct iscsi_tpg_np *tpg_np = to_iscsi_tpg_np(item);
	struct iscsi_np *np;
	struct iscsi_portal_group *tpg;
	struct iscsi_tpg_np *tpg_np_new = NULL;
	u32 op;
	int rc;

	rc = kstrtou32(page, 0, &op);
	if (rc)
		return rc;
	if ((op != 1) && (op != 0)) {
		pr_err("Illegal value for tpg_enable: %u\n", op);
		return -EINVAL;
	}
	np = tpg_np->tpg_np;
	if (!np) {
		pr_err("Unable to locate struct iscsi_np from"
				" struct iscsi_tpg_np\n");
		return -EINVAL;
	}

	tpg = tpg_np->tpg;
	if (iscsit_get_tpg(tpg) < 0)
		return -EINVAL;

	if (op) {
		if (strlen(mod_name)) {
			rc = request_module(mod_name);
			if (rc != 0) {
				pr_warn("Unable to request_module for %s\n",
					mod_name);
				rc = 0;
			}
		}

		tpg_np_new = iscsit_tpg_add_network_portal(tpg,
					&np->np_sockaddr, tpg_np, type);
		if (IS_ERR(tpg_np_new)) {
			rc = PTR_ERR(tpg_np_new);
			goto out;
		}
	} else {
		tpg_np_new = iscsit_tpg_locate_child_np(tpg_np, type);
		if (tpg_np_new) {
			rc = iscsit_tpg_del_network_portal(tpg, tpg_np_new);
			if (rc < 0)
				goto out;
		}
	}

	iscsit_put_tpg(tpg);
	return count;
out:
	iscsit_put_tpg(tpg);
	return rc;
}