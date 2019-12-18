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
struct pdc_state {int last_rx_curr; TYPE_1__* rxregs_64; } ;
struct TYPE_2__ {int /*<<< orphan*/  status0; } ;

/* Variables and functions */
 int CRYPTO_D64_RS0_CD_MASK ; 
 int PDC_SUCCESS ; 
 int RING_ENTRY_SIZE ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int pdc_receive_one (struct pdc_state*) ; 

__attribute__((used)) static int
pdc_receive(struct pdc_state *pdcs)
{
	int rx_status;

	/* read last_rx_curr from register once */
	pdcs->last_rx_curr =
	    (ioread32(&pdcs->rxregs_64->status0) &
	     CRYPTO_D64_RS0_CD_MASK) / RING_ENTRY_SIZE;

	do {
		/* Could be many frames ready */
		rx_status = pdc_receive_one(pdcs);
	} while (rx_status == PDC_SUCCESS);

	return 0;
}