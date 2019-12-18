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
struct t10_alua_tg_pt_gp {unsigned char tg_pt_gp_alua_access_type; } ;
struct se_lun {int /*<<< orphan*/  lun_tg_pt_gp_lock; struct t10_alua_tg_pt_gp* lun_tg_pt_gp; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spc_fill_alua_data(struct se_lun *lun, unsigned char *buf)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp;

	/*
	 * Set SCCS for MAINTENANCE_IN + REPORT_TARGET_PORT_GROUPS.
	 */
	buf[5]	= 0x80;

	/*
	 * Set TPGS field for explicit and/or implicit ALUA access type
	 * and opteration.
	 *
	 * See spc4r17 section 6.4.2 Table 135
	 */
	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	if (tg_pt_gp)
		buf[5] |= tg_pt_gp->tg_pt_gp_alua_access_type;
	spin_unlock(&lun->lun_tg_pt_gp_lock);
}