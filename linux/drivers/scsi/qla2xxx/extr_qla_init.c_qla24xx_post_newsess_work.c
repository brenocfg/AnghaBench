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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_qla_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; int /*<<< orphan*/  fc4_type; void* pla; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {TYPE_2__ new_sess; } ;
struct qla_work_evt {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  port_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_EVT_NEW_SESS ; 
 int QLA_FUNCTION_FAILED ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 

int qla24xx_post_newsess_work(struct scsi_qla_host *vha, port_id_t *id,
    u8 *port_name, u8 *node_name, void *pla, u8 fc4_type)
{
	struct qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_NEW_SESS);
	if (!e)
		return QLA_FUNCTION_FAILED;

	e->u.new_sess.id = *id;
	e->u.new_sess.pla = pla;
	e->u.new_sess.fc4_type = fc4_type;
	memcpy(e->u.new_sess.port_name, port_name, WWN_SIZE);
	if (node_name)
		memcpy(e->u.new_sess.node_name, node_name, WWN_SIZE);

	return qla2x00_post_work(vha, e);
}