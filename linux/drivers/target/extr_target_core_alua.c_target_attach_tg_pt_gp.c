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
struct t10_alua_tg_pt_gp {int dummy; } ;
struct se_lun {int /*<<< orphan*/  lun_tg_pt_gp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __target_attach_tg_pt_gp (struct se_lun*,struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void target_attach_tg_pt_gp(struct se_lun *lun,
		struct t10_alua_tg_pt_gp *tg_pt_gp)
{
	spin_lock(&lun->lun_tg_pt_gp_lock);
	__target_attach_tg_pt_gp(lun, tg_pt_gp);
	spin_unlock(&lun->lun_tg_pt_gp_lock);
}