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
union fotg210_shadow {struct fotg210_itd* itd; scalar_t__ ptr; } ;
struct fotg210_itd {unsigned int frame; int itd_dma; scalar_t__ hw_next; union fotg210_shadow itd_next; } ;
struct fotg210_hcd {scalar_t__* periodic; union fotg210_shadow* pshadow; } ;
typedef  scalar_t__ __hc32 ;

/* Variables and functions */
 scalar_t__ Q_NEXT_TYPE (struct fotg210_hcd*,scalar_t__) ; 
 int Q_TYPE_ITD ; 
 int Q_TYPE_QH ; 
 scalar_t__ cpu_to_hc32 (struct fotg210_hcd*,int) ; 
 union fotg210_shadow* periodic_next_shadow (struct fotg210_hcd*,union fotg210_shadow*,scalar_t__) ; 
 scalar_t__* shadow_next_periodic (struct fotg210_hcd*,union fotg210_shadow*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void itd_link(struct fotg210_hcd *fotg210, unsigned frame,
		struct fotg210_itd *itd)
{
	union fotg210_shadow *prev = &fotg210->pshadow[frame];
	__hc32 *hw_p = &fotg210->periodic[frame];
	union fotg210_shadow here = *prev;
	__hc32 type = 0;

	/* skip any iso nodes which might belong to previous microframes */
	while (here.ptr) {
		type = Q_NEXT_TYPE(fotg210, *hw_p);
		if (type == cpu_to_hc32(fotg210, Q_TYPE_QH))
			break;
		prev = periodic_next_shadow(fotg210, prev, type);
		hw_p = shadow_next_periodic(fotg210, &here, type);
		here = *prev;
	}

	itd->itd_next = here;
	itd->hw_next = *hw_p;
	prev->itd = itd;
	itd->frame = frame;
	wmb();
	*hw_p = cpu_to_hc32(fotg210, itd->itd_dma | Q_TYPE_ITD);
}