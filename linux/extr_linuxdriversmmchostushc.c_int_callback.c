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
typedef  int u8 ;
struct ushc_data {int last_status; int /*<<< orphan*/  int_urb; int /*<<< orphan*/  flags; int /*<<< orphan*/  mmc; TYPE_1__* int_data; } ;
struct urb {scalar_t__ status; struct ushc_data* context; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IGNORE_NEXT_INT ; 
 int /*<<< orphan*/  INT_EN ; 
 int USHC_INT_STATUS_CARD_PRESENT ; 
 int USHC_INT_STATUS_SDIO_INT ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int_callback(struct urb *urb)
{
	struct ushc_data *ushc = urb->context;
	u8 status, last_status;

	if (urb->status < 0)
		return;

	status = ushc->int_data->status;
	last_status = ushc->last_status;
	ushc->last_status = status;

	/*
	 * Ignore the card interrupt status on interrupt transfers that
	 * were submitted while card interrupts where disabled.
	 *
	 * This avoid occasional spurious interrupts when enabling
	 * interrupts immediately after clearing the source on the card.
	 */

	if (!test_and_clear_bit(IGNORE_NEXT_INT, &ushc->flags)
	    && test_bit(INT_EN, &ushc->flags)
	    && status & USHC_INT_STATUS_SDIO_INT) {
		mmc_signal_sdio_irq(ushc->mmc);
	}

	if ((status ^ last_status) & USHC_INT_STATUS_CARD_PRESENT)
		mmc_detect_change(ushc->mmc, msecs_to_jiffies(100));

	if (!test_bit(INT_EN, &ushc->flags))
		set_bit(IGNORE_NEXT_INT, &ushc->flags);
	usb_submit_urb(ushc->int_urb, GFP_ATOMIC);
}