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
typedef  int /*<<< orphan*/  u64 ;
struct se_portal_group {int dummy; } ;
struct se_lun {struct se_portal_group* lun_tpg; int /*<<< orphan*/  lun_tg_pt_gp_lock; int /*<<< orphan*/  lun_tg_pt_gp_link; int /*<<< orphan*/  lun_tg_pt_md_mutex; int /*<<< orphan*/  lun_deve_lock; int /*<<< orphan*/  lun_tg_pt_secondary_offline; int /*<<< orphan*/  lun_dev_link; int /*<<< orphan*/  lun_deve_list; int /*<<< orphan*/  lun_shutdown_comp; int /*<<< orphan*/  lun_acl_count; int /*<<< orphan*/  unpacked_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct se_lun* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct se_lun* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct se_lun *core_tpg_alloc_lun(
	struct se_portal_group *tpg,
	u64 unpacked_lun)
{
	struct se_lun *lun;

	lun = kzalloc(sizeof(*lun), GFP_KERNEL);
	if (!lun) {
		pr_err("Unable to allocate se_lun memory\n");
		return ERR_PTR(-ENOMEM);
	}
	lun->unpacked_lun = unpacked_lun;
	atomic_set(&lun->lun_acl_count, 0);
	init_completion(&lun->lun_shutdown_comp);
	INIT_LIST_HEAD(&lun->lun_deve_list);
	INIT_LIST_HEAD(&lun->lun_dev_link);
	atomic_set(&lun->lun_tg_pt_secondary_offline, 0);
	spin_lock_init(&lun->lun_deve_lock);
	mutex_init(&lun->lun_tg_pt_md_mutex);
	INIT_LIST_HEAD(&lun->lun_tg_pt_gp_link);
	spin_lock_init(&lun->lun_tg_pt_gp_lock);
	lun->lun_tpg = tpg;

	return lun;
}