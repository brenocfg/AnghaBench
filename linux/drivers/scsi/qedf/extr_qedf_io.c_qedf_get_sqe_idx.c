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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u16 ;
struct qedf_rport {int sq_mem_size; scalar_t__ sq_prod_idx; int /*<<< orphan*/  fw_sq_prod_idx; } ;
struct fcoe_wqe {int dummy; } ;

/* Variables and functions */

u16 qedf_get_sqe_idx(struct qedf_rport *fcport)
{
	uint16_t total_sqe = (fcport->sq_mem_size)/(sizeof(struct fcoe_wqe));
	u16 rval;

	rval = fcport->sq_prod_idx;

	/* Adjust ring index */
	fcport->sq_prod_idx++;
	fcport->fw_sq_prod_idx++;
	if (fcport->sq_prod_idx == total_sqe)
		fcport->sq_prod_idx = 0;

	return rval;
}