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
typedef  int /*<<< orphan*/  u8 ;
struct hfi1_pportdata {TYPE_1__* dd; } ;
struct hfi1_ibport {int dummy; } ;
struct hfi1_ibdev {int /*<<< orphan*/  rdi; } ;
struct TYPE_2__ {struct hfi1_ibdev verbs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_qp_iter_cb ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  rvt_qp_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfi1_error_port_qps(struct hfi1_ibport *ibp, u8 sl)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	struct hfi1_ibdev *dev = &ppd->dd->verbs_dev;

	rvt_qp_iter(&dev->rdi, sl, hfi1_qp_iter_cb);
}