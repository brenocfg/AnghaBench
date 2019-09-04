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
struct sge_rspq {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  intr_params; int /*<<< orphan*/  adapter; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int CIDXINC_V (int /*<<< orphan*/ ) ; 
 int INGRESSQID_V (int /*<<< orphan*/ ) ; 
 int SEINTARM_V (int /*<<< orphan*/ ) ; 
 scalar_t__ SGE_VF_GTS ; 
 scalar_t__ T4VF_SGE_BASE_ADDR ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void qenable(struct sge_rspq *rspq)
{
	napi_enable(&rspq->napi);

	/*
	 * 0-increment the Going To Sleep register to start the timer and
	 * enable interrupts.
	 */
	t4_write_reg(rspq->adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
		     CIDXINC_V(0) |
		     SEINTARM_V(rspq->intr_params) |
		     INGRESSQID_V(rspq->cntxt_id));
}