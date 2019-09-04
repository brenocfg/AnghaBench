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
struct rvt_qp {struct qib_qp_priv* priv; } ;
struct rvt_dev_info {int dummy; } ;
struct qib_qp_priv {struct qib_qp_priv* s_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qib_qp_priv*) ; 

void qib_qp_priv_free(struct rvt_dev_info *rdi, struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;

	kfree(priv->s_hdr);
	kfree(priv);
}