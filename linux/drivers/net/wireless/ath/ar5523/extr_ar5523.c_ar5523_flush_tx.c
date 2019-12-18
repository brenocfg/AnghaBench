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
struct ar5523 {int /*<<< orphan*/  tx_nr_pending; int /*<<< orphan*/  tx_nr_total; int /*<<< orphan*/  tx_flush_waitq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_FLUSH_TIMEOUT ; 
 int /*<<< orphan*/  AR5523_USB_DISCONNECTED ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_tx_work_locked (struct ar5523*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar5523_flush_tx(struct ar5523 *ar)
{
	ar5523_tx_work_locked(ar);

	/* Don't waste time trying to flush if USB is disconnected */
	if (test_bit(AR5523_USB_DISCONNECTED, &ar->flags))
		return;
	if (!wait_event_timeout(ar->tx_flush_waitq,
	    !atomic_read(&ar->tx_nr_pending), AR5523_FLUSH_TIMEOUT))
		ar5523_err(ar, "flush timeout (tot %d pend %d)\n",
			   atomic_read(&ar->tx_nr_total),
			   atomic_read(&ar->tx_nr_pending));
}