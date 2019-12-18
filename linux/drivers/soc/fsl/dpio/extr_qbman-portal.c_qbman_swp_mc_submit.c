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
typedef  int u8 ;
struct TYPE_4__ {int valid_bit; } ;
struct qbman_swp {TYPE_2__ mc; TYPE_1__* desc; } ;
struct TYPE_3__ {int qman_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  QBMAN_CINH_SWP_CR_RT ; 
 int QMAN_REV_5000 ; 
 int QMAN_REV_MASK ; 
 int /*<<< orphan*/  QMAN_RT_MODE ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  qbman_write_register (struct qbman_swp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qbman_swp_mc_submit(struct qbman_swp *p, void *cmd, u8 cmd_verb)
{
	u8 *v = cmd;

	if ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000) {
		dma_wmb();
		*v = cmd_verb | p->mc.valid_bit;
	} else {
		*v = cmd_verb | p->mc.valid_bit;
		dma_wmb();
		qbman_write_register(p, QBMAN_CINH_SWP_CR_RT, QMAN_RT_MODE);
	}
}