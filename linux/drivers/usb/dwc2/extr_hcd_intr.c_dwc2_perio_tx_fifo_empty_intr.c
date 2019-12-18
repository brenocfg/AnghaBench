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
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_TRANSACTION_PERIODIC ; 
 scalar_t__ dbg_perio () ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_hcd_queue_transactions (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_perio_tx_fifo_empty_intr(struct dwc2_hsotg *hsotg)
{
	if (dbg_perio())
		dev_vdbg(hsotg->dev, "--Periodic TxFIFO Empty Interrupt--\n");
	dwc2_hcd_queue_transactions(hsotg, DWC2_TRANSACTION_PERIODIC);
}