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
struct TYPE_4__ {TYPE_1__* sel_fcf; } ;
struct qedf_ctx {TYPE_2__ ctlr; } ;
struct fc_lport {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int fka_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 struct qedf_ctx* qedf_get_base_qedf (struct qedf_ctx*) ; 
 scalar_t__ qedf_is_vport (struct qedf_ctx*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qedf_fka_period_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct fc_lport *lport = shost_priv(class_to_shost(dev));
	struct qedf_ctx *qedf = lport_priv(lport);
	int fka_period = -1;

	if (qedf_is_vport(qedf))
		qedf = qedf_get_base_qedf(qedf);

	if (qedf->ctlr.sel_fcf)
		fka_period = qedf->ctlr.sel_fcf->fka_period;

	return scnprintf(buf, PAGE_SIZE, "%d\n", fka_period);
}