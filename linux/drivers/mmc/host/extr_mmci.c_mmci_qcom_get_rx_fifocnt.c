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
typedef  int u32 ;
struct mmci_host {TYPE_1__* variant; } ;
struct TYPE_2__ {int fifohalfsize; } ;

/* Variables and functions */
 int MCI_RXDATAAVLBL ; 
 int MCI_RXFIFOHALFFULL ; 

__attribute__((used)) static int mmci_qcom_get_rx_fifocnt(struct mmci_host *host, u32 status, int r)
{
	/*
	 * on qcom SDCC4 only 8 words are used in each burst so only 8 addresses
	 * from the fifo range should be used
	 */
	if (status & MCI_RXFIFOHALFFULL)
		return host->variant->fifohalfsize;
	else if (status & MCI_RXDATAAVLBL)
		return 4;

	return 0;
}