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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int dummy; } ;
struct TYPE_3__ {int code; int /*<<< orphan*/  data; int /*<<< orphan*/  data_size; } ;
struct TYPE_4__ {TYPE_1__ aen; } ;
struct qla4_work_evt {TYPE_2__ u; } ;
typedef  enum iscsi_host_event_code { ____Placeholder_iscsi_host_event_code } iscsi_host_event_code ;

/* Variables and functions */
 int /*<<< orphan*/  QLA4_EVENT_AEN ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qla4_work_evt* qla4xxx_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4xxx_post_work (struct scsi_qla_host*,struct qla4_work_evt*) ; 

int qla4xxx_post_aen_work(struct scsi_qla_host *ha,
			  enum iscsi_host_event_code aen_code,
			  uint32_t data_size, uint8_t *data)
{
	struct qla4_work_evt *e;

	e = qla4xxx_alloc_work(ha, data_size, QLA4_EVENT_AEN);
	if (!e)
		return QLA_ERROR;

	e->u.aen.code = aen_code;
	e->u.aen.data_size = data_size;
	memcpy(e->u.aen.data, data, data_size);

	qla4xxx_post_work(ha, e);

	return QLA_SUCCESS;
}