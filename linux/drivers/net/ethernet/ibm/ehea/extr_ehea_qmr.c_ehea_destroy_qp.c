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
typedef  scalar_t__ u64 ;
struct ehea_qp {int /*<<< orphan*/  fw_handle; int /*<<< orphan*/  adapter; int /*<<< orphan*/  epas; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FORCE_FREE ; 
 scalar_t__ H_R_STATE ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  NORMAL_FREE ; 
 scalar_t__ ehea_destroy_qp_res (struct ehea_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_error_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  hcp_epas_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int ehea_destroy_qp(struct ehea_qp *qp)
{
	u64 hret, aer, aerr;
	if (!qp)
		return 0;

	hcp_epas_dtor(&qp->epas);

	hret = ehea_destroy_qp_res(qp, NORMAL_FREE);
	if (hret == H_R_STATE) {
		ehea_error_data(qp->adapter, qp->fw_handle, &aer, &aerr);
		hret = ehea_destroy_qp_res(qp, FORCE_FREE);
	}

	if (hret != H_SUCCESS) {
		pr_err("destroy QP failed\n");
		return -EIO;
	}

	return 0;
}