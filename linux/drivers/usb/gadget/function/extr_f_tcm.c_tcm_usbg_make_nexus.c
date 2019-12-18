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
struct usbg_tpg {int /*<<< orphan*/  tpg_mutex; int /*<<< orphan*/  se_tpg; scalar_t__ tpg_nexus; } ;
struct usbg_cmd {int dummy; } ;
struct tcm_usbg_nexus {int /*<<< orphan*/  tvn_se_sess; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_NEXUS_MSG ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PROT_NORMAL ; 
 int /*<<< orphan*/  USB_G_DEFAULT_SESSION_TAGS ; 
 int /*<<< orphan*/  kfree (struct tcm_usbg_nexus*) ; 
 struct tcm_usbg_nexus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  target_setup_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct tcm_usbg_nexus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbg_alloc_sess_cb ; 

__attribute__((used)) static int tcm_usbg_make_nexus(struct usbg_tpg *tpg, char *name)
{
	struct tcm_usbg_nexus *tv_nexus;
	int ret = 0;

	mutex_lock(&tpg->tpg_mutex);
	if (tpg->tpg_nexus) {
		ret = -EEXIST;
		pr_debug("tpg->tpg_nexus already exists\n");
		goto out_unlock;
	}

	tv_nexus = kzalloc(sizeof(*tv_nexus), GFP_KERNEL);
	if (!tv_nexus) {
		ret = -ENOMEM;
		goto out_unlock;
	}

	tv_nexus->tvn_se_sess = target_setup_session(&tpg->se_tpg,
						     USB_G_DEFAULT_SESSION_TAGS,
						     sizeof(struct usbg_cmd),
						     TARGET_PROT_NORMAL, name,
						     tv_nexus, usbg_alloc_sess_cb);
	if (IS_ERR(tv_nexus->tvn_se_sess)) {
#define MAKE_NEXUS_MSG "core_tpg_check_initiator_node_acl() failed for %s\n"
		pr_debug(MAKE_NEXUS_MSG, name);
#undef MAKE_NEXUS_MSG
		ret = PTR_ERR(tv_nexus->tvn_se_sess);
		kfree(tv_nexus);
	}

out_unlock:
	mutex_unlock(&tpg->tpg_mutex);
	return ret;
}