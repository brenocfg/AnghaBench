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
struct pdc_state {int rxout; int txout; int /*<<< orphan*/  pdc_requests; TYPE_2__* txregs_64; TYPE_1__* rxregs_64; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int PDC_SUCCESS ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int pdc_tx_list_final(struct pdc_state *pdcs)
{
	/*
	 * write barrier to ensure all register writes are complete
	 * before chip starts to process new request
	 */
	wmb();
	iowrite32(pdcs->rxout << 4, &pdcs->rxregs_64->ptr);
	iowrite32(pdcs->txout << 4, &pdcs->txregs_64->ptr);
	pdcs->pdc_requests++;

	return PDC_SUCCESS;
}