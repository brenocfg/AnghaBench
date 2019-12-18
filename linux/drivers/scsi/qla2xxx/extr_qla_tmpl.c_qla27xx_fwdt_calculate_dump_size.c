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
typedef  int /*<<< orphan*/  ulong ;
struct scsi_qla_host {int dummy; } ;
struct qla27xx_fwdt_template {int /*<<< orphan*/  template_size; } ;

/* Variables and functions */
 scalar_t__ qla27xx_fwdt_template_valid (struct qla27xx_fwdt_template*) ; 
 int /*<<< orphan*/  qla27xx_walk_template (struct scsi_qla_host*,struct qla27xx_fwdt_template*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ulong
qla27xx_fwdt_calculate_dump_size(struct scsi_qla_host *vha, void *p)
{
	struct qla27xx_fwdt_template *tmp = p;
	ulong len = 0;

	if (qla27xx_fwdt_template_valid(tmp)) {
		len = tmp->template_size;
		qla27xx_walk_template(vha, tmp, NULL, &len);
	}

	return len;
}