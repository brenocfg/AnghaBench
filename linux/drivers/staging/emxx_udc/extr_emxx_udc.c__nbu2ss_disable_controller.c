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
struct nbu2ss_udc {int udc_enabled; TYPE_1__* p_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  EPCTR; } ;

/* Variables and functions */
 int DIRPD ; 
 int EPC_RST ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _nbu2ss_reset_controller (struct nbu2ss_udc*) ; 

__attribute__((used)) static void _nbu2ss_disable_controller(struct nbu2ss_udc *udc)
{
	if (udc->udc_enabled) {
		udc->udc_enabled = false;
		_nbu2ss_reset_controller(udc);
		_nbu2ss_bitset(&udc->p_regs->EPCTR, (DIRPD | EPC_RST));
	}
}