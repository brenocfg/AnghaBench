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
struct fman_port {TYPE_2__* bmi_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  fmbm_rfpne; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;

/* Variables and functions */
 int NIA_BMI_AC_ENQ_FRAME ; 
 int NIA_ENG_BMI ; 
 int NIA_ENG_HWK ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_port_use_kg_hash(struct fman_port *port, bool enable)
{
	if (enable)
		/* After the Parser frames go to KeyGen */
		iowrite32be(NIA_ENG_HWK, &port->bmi_regs->rx.fmbm_rfpne);
	else
		/* After the Parser frames go to BMI */
		iowrite32be(NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME,
			    &port->bmi_regs->rx.fmbm_rfpne);
}