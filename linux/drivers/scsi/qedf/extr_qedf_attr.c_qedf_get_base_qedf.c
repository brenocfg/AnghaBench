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
struct qedf_ctx {struct fc_lport* lport; } ;
struct fc_lport {int /*<<< orphan*/  vport; } ;

/* Variables and functions */
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  qedf_is_vport (struct qedf_ctx*) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vport_to_shost (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qedf_ctx *qedf_get_base_qedf(struct qedf_ctx *qedf)
{
	struct fc_lport *lport;
	struct fc_lport *base_lport;

	if (!(qedf_is_vport(qedf)))
		return NULL;

	lport = qedf->lport;
	base_lport = shost_priv(vport_to_shost(lport->vport));
	return lport_priv(base_lport);
}