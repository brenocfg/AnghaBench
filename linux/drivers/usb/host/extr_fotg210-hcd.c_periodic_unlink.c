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
union fotg210_shadow {void* ptr; } ;
struct fotg210_hcd {int /*<<< orphan*/ * periodic; union fotg210_shadow* pshadow; } ;
typedef  int /*<<< orphan*/  __hc32 ;

/* Variables and functions */
 int /*<<< orphan*/  Q_NEXT_TYPE (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 
 union fotg210_shadow* periodic_next_shadow (struct fotg210_hcd*,union fotg210_shadow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shadow_next_periodic (struct fotg210_hcd*,union fotg210_shadow*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void periodic_unlink(struct fotg210_hcd *fotg210, unsigned frame,
		void *ptr)
{
	union fotg210_shadow *prev_p = &fotg210->pshadow[frame];
	__hc32 *hw_p = &fotg210->periodic[frame];
	union fotg210_shadow here = *prev_p;

	/* find predecessor of "ptr"; hw and shadow lists are in sync */
	while (here.ptr && here.ptr != ptr) {
		prev_p = periodic_next_shadow(fotg210, prev_p,
				Q_NEXT_TYPE(fotg210, *hw_p));
		hw_p = shadow_next_periodic(fotg210, &here,
				Q_NEXT_TYPE(fotg210, *hw_p));
		here = *prev_p;
	}
	/* an interrupt entry (at list end) could have been shared */
	if (!here.ptr)
		return;

	/* update shadow and hardware lists ... the old "next" pointers
	 * from ptr may still be in use, the caller updates them.
	 */
	*prev_p = *periodic_next_shadow(fotg210, &here,
			Q_NEXT_TYPE(fotg210, *hw_p));

	*hw_p = *shadow_next_periodic(fotg210, &here,
			Q_NEXT_TYPE(fotg210, *hw_p));
}