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
struct fotg210_hcd {int scanning; int need_rescan; scalar_t__ intr_count; scalar_t__ isoc_count; scalar_t__ async_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  scan_async (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  scan_intr (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  scan_isoc (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  turn_on_io_watchdog (struct fotg210_hcd*) ; 

__attribute__((used)) static void fotg210_work(struct fotg210_hcd *fotg210)
{
	/* another CPU may drop fotg210->lock during a schedule scan while
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	if (fotg210->scanning) {
		fotg210->need_rescan = true;
		return;
	}
	fotg210->scanning = true;

rescan:
	fotg210->need_rescan = false;
	if (fotg210->async_count)
		scan_async(fotg210);
	if (fotg210->intr_count > 0)
		scan_intr(fotg210);
	if (fotg210->isoc_count > 0)
		scan_isoc(fotg210);
	if (fotg210->need_rescan)
		goto rescan;
	fotg210->scanning = false;

	/* the IO watchdog guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	turn_on_io_watchdog(fotg210);
}