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
union ehci_shadow {TYPE_1__* qh; scalar_t__ ptr; } ;
struct oxu_hcd {union ehci_shadow* pshadow; int /*<<< orphan*/ * periodic; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int hw_info2; unsigned int usecs; unsigned int c_usecs; union ehci_shadow qh_next; int /*<<< orphan*/  hw_next; } ;

/* Variables and functions */
 int Q_NEXT_TYPE (int /*<<< orphan*/ ) ; 
#define  Q_TYPE_QH 128 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  oxu_err (struct oxu_hcd*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned short periodic_usecs(struct oxu_hcd *oxu,
					unsigned frame, unsigned uframe)
{
	__le32 *hw_p = &oxu->periodic[frame];
	union ehci_shadow *q = &oxu->pshadow[frame];
	unsigned usecs = 0;

	while (q->ptr) {
		switch (Q_NEXT_TYPE(*hw_p)) {
		case Q_TYPE_QH:
		default:
			/* is it in the S-mask? */
			if (q->qh->hw_info2 & cpu_to_le32(1 << uframe))
				usecs += q->qh->usecs;
			/* ... or C-mask? */
			if (q->qh->hw_info2 & cpu_to_le32(1 << (8 + uframe)))
				usecs += q->qh->c_usecs;
			hw_p = &q->qh->hw_next;
			q = &q->qh->qh_next;
			break;
		}
	}
#ifdef DEBUG
	if (usecs > 100)
		oxu_err(oxu, "uframe %d sched overrun: %d usecs\n",
						frame * 8 + uframe, usecs);
#endif
	return usecs;
}