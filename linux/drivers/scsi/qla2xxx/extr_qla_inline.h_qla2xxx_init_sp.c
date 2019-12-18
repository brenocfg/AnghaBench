#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qla_qpair {int dummy; } ;
struct TYPE_4__ {int iocbs; int /*<<< orphan*/  elem; int /*<<< orphan*/  cmd_type; struct qla_qpair* qpair; int /*<<< orphan*/ * vha; int /*<<< orphan*/ * fcport; } ;
typedef  TYPE_1__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_SRB ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qla2xxx_init_sp(srb_t *sp, scsi_qla_host_t *vha,
			    struct qla_qpair *qpair, fc_port_t *fcport)
{
	memset(sp, 0, sizeof(*sp));
	sp->fcport = fcport;
	sp->iocbs = 1;
	sp->vha = vha;
	sp->qpair = qpair;
	sp->cmd_type = TYPE_SRB;
	INIT_LIST_HEAD(&sp->elem);
}