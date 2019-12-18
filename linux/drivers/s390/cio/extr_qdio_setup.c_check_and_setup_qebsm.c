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
struct TYPE_2__ {int rflags; } ;
struct qdio_irq {unsigned long sch_token; TYPE_1__ qib; } ;

/* Variables and functions */
 unsigned char AC1_SC_QEBSM_AVAILABLE ; 
 unsigned char AC1_SC_QEBSM_ENABLED ; 
 int /*<<< orphan*/  DBF_EVENT (char*,...) ; 
 int QIB_RFLAGS_ENABLE_QEBSM ; 

__attribute__((used)) static void check_and_setup_qebsm(struct qdio_irq *irq_ptr,
				  unsigned char qdioac, unsigned long token)
{
	if (!(irq_ptr->qib.rflags & QIB_RFLAGS_ENABLE_QEBSM))
		goto no_qebsm;
	if (!(qdioac & AC1_SC_QEBSM_AVAILABLE) ||
	    (!(qdioac & AC1_SC_QEBSM_ENABLED)))
		goto no_qebsm;

	irq_ptr->sch_token = token;

	DBF_EVENT("V=V:1");
	DBF_EVENT("%8lx", irq_ptr->sch_token);
	return;

no_qebsm:
	irq_ptr->sch_token = 0;
	irq_ptr->qib.rflags &= ~QIB_RFLAGS_ENABLE_QEBSM;
	DBF_EVENT("noV=V");
}