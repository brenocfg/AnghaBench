#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usnic_ib_qp_grp {int /*<<< orphan*/  grp_id; int /*<<< orphan*/  kobj; TYPE_1__* vf; } ;
struct usnic_ib_dev {int /*<<< orphan*/  qpn_kobj; } ;
struct TYPE_2__ {struct usnic_ib_dev* pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ ) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_ib_qpn_type ; 

void usnic_ib_sysfs_qpn_add(struct usnic_ib_qp_grp *qp_grp)
{
	struct usnic_ib_dev *us_ibdev;
	int err;

	us_ibdev = qp_grp->vf->pf;

	err = kobject_init_and_add(&qp_grp->kobj, &usnic_ib_qpn_type,
			kobject_get(us_ibdev->qpn_kobj),
			"%d", qp_grp->grp_id);
	if (err) {
		kobject_put(us_ibdev->qpn_kobj);
		return;
	}
}