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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_INITIALIZED (struct ar9170*) ; 
 scalar_t__ IS_STARTED (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_tx_scheduler (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_rx_work (struct ar9170*) ; 

__attribute__((used)) static void carl9170_usb_tasklet(unsigned long data)
{
	struct ar9170 *ar = (struct ar9170 *) data;

	if (!IS_INITIALIZED(ar))
		return;

	carl9170_usb_rx_work(ar);

	/*
	 * Strictly speaking: The tx scheduler is not part of the USB system.
	 * But the rx worker returns frames back to the mac80211-stack and
	 * this is the _perfect_ place to generate the next transmissions.
	 */
	if (IS_STARTED(ar))
		carl9170_tx_scheduler(ar);
}