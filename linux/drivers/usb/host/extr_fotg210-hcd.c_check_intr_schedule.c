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
typedef  int u8 ;
struct fotg210_qh {unsigned int gap_uf; scalar_t__ c_usecs; int /*<<< orphan*/  period; int /*<<< orphan*/  dev; scalar_t__ usecs; } ;
struct fotg210_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc32 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  check_period (struct fotg210_hcd*,unsigned int,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_hc32 (struct fotg210_hcd*,int) ; 
 scalar_t__ tt_no_collision (struct fotg210_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int check_intr_schedule(struct fotg210_hcd *fotg210, unsigned frame,
		unsigned uframe, const struct fotg210_qh *qh, __hc32 *c_maskp)
{
	int retval = -ENOSPC;
	u8 mask = 0;

	if (qh->c_usecs && uframe >= 6)		/* FSTN territory? */
		goto done;

	if (!check_period(fotg210, frame, uframe, qh->period, qh->usecs))
		goto done;
	if (!qh->c_usecs) {
		retval = 0;
		*c_maskp = 0;
		goto done;
	}

	/* Make sure this tt's buffer is also available for CSPLITs.
	 * We pessimize a bit; probably the typical full speed case
	 * doesn't need the second CSPLIT.
	 *
	 * NOTE:  both SPLIT and CSPLIT could be checked in just
	 * one smart pass...
	 */
	mask = 0x03 << (uframe + qh->gap_uf);
	*c_maskp = cpu_to_hc32(fotg210, mask << 8);

	mask |= 1 << uframe;
	if (tt_no_collision(fotg210, qh->period, qh->dev, frame, mask)) {
		if (!check_period(fotg210, frame, uframe + qh->gap_uf + 1,
				qh->period, qh->c_usecs))
			goto done;
		if (!check_period(fotg210, frame, uframe + qh->gap_uf,
				qh->period, qh->c_usecs))
			goto done;
		retval = 0;
	}
done:
	return retval;
}