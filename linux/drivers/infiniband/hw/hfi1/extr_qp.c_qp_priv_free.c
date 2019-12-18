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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct rvt_dev_info {int dummy; } ;
struct hfi1_qp_priv {struct hfi1_qp_priv* s_ahg; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_qp_priv_tid_free (struct rvt_dev_info*,struct rvt_qp*) ; 
 int /*<<< orphan*/  kfree (struct hfi1_qp_priv*) ; 

void qp_priv_free(struct rvt_dev_info *rdi, struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;

	hfi1_qp_priv_tid_free(rdi, qp);
	kfree(priv->s_ahg);
	kfree(priv);
}