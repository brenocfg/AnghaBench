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
struct qbman_swp {TYPE_1__* desc; } ;
struct TYPE_2__ {int qman_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  QBMAN_CENA_SWP_CR ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_CR_MEM ; 
 int QMAN_REV_5000 ; 
 int QMAN_REV_MASK ; 
 void* qbman_get_cmd (struct qbman_swp*,int /*<<< orphan*/ ) ; 

void *qbman_swp_mc_start(struct qbman_swp *p)
{
	if ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000)
		return qbman_get_cmd(p, QBMAN_CENA_SWP_CR);
	else
		return qbman_get_cmd(p, QBMAN_CENA_SWP_CR_MEM);
}