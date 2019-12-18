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
struct qbman_swp {int dummy; } ;
struct dpaa2_dq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QBMAN_CINH_SWP_DCAP ; 
 int /*<<< orphan*/  QBMAN_IDX_FROM_DQRR (struct dpaa2_dq const*) ; 
 int /*<<< orphan*/  qbman_write_register (struct qbman_swp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qbman_swp_dqrr_consume(struct qbman_swp *s, const struct dpaa2_dq *dq)
{
	qbman_write_register(s, QBMAN_CINH_SWP_DCAP, QBMAN_IDX_FROM_DQRR(dq));
}