#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rc; } ;
union qm_mr_entry {TYPE_1__ ern; } ;
struct TYPE_4__ {int /*<<< orphan*/  orp_zero; int /*<<< orphan*/  fq_retired; int /*<<< orphan*/  fq_tdrop; int /*<<< orphan*/  late_window; int /*<<< orphan*/  early_window; int /*<<< orphan*/  err_cond; int /*<<< orphan*/  wred; int /*<<< orphan*/  cg_tdrop; } ;
struct dpaa_percpu_priv {TYPE_2__ ern_cnt; } ;

/* Variables and functions */
#define  QM_MR_RC_CGR_TAILDROP 135 
#define  QM_MR_RC_ERROR 134 
#define  QM_MR_RC_FQ_TAILDROP 133 
 int QM_MR_RC_MASK ; 
#define  QM_MR_RC_ORPWINDOW_EARLY 132 
#define  QM_MR_RC_ORPWINDOW_LATE 131 
#define  QM_MR_RC_ORPWINDOW_RETIRED 130 
#define  QM_MR_RC_ORP_ZERO 129 
#define  QM_MR_RC_WRED 128 

__attribute__((used)) static void count_ern(struct dpaa_percpu_priv *percpu_priv,
		      const union qm_mr_entry *msg)
{
	switch (msg->ern.rc & QM_MR_RC_MASK) {
	case QM_MR_RC_CGR_TAILDROP:
		percpu_priv->ern_cnt.cg_tdrop++;
		break;
	case QM_MR_RC_WRED:
		percpu_priv->ern_cnt.wred++;
		break;
	case QM_MR_RC_ERROR:
		percpu_priv->ern_cnt.err_cond++;
		break;
	case QM_MR_RC_ORPWINDOW_EARLY:
		percpu_priv->ern_cnt.early_window++;
		break;
	case QM_MR_RC_ORPWINDOW_LATE:
		percpu_priv->ern_cnt.late_window++;
		break;
	case QM_MR_RC_FQ_TAILDROP:
		percpu_priv->ern_cnt.fq_tdrop++;
		break;
	case QM_MR_RC_ORPWINDOW_RETIRED:
		percpu_priv->ern_cnt.fq_retired++;
		break;
	case QM_MR_RC_ORP_ZERO:
		percpu_priv->ern_cnt.orp_zero++;
		break;
	}
}