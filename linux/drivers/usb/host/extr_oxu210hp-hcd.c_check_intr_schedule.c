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
struct oxu_hcd {int dummy; } ;
struct ehci_qh {scalar_t__ c_usecs; int /*<<< orphan*/  usecs; int /*<<< orphan*/  period; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  check_period (struct oxu_hcd*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_intr_schedule(struct oxu_hcd	*oxu,
				unsigned frame, unsigned uframe,
				const struct ehci_qh *qh, __le32 *c_maskp)
{
	int retval = -ENOSPC;

	if (qh->c_usecs && uframe >= 6)		/* FSTN territory? */
		goto done;

	if (!check_period(oxu, frame, uframe, qh->period, qh->usecs))
		goto done;
	if (!qh->c_usecs) {
		retval = 0;
		*c_maskp = 0;
		goto done;
	}

done:
	return retval;
}