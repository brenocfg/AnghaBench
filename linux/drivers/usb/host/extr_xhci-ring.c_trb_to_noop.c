#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * field; } ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;
union xhci_trb {TYPE_2__ generic; TYPE_1__ link; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  TRB_CHAIN ; 
 int /*<<< orphan*/  TRB_CYCLE ; 
 int /*<<< orphan*/  TRB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ trb_is_link (union xhci_trb*) ; 

__attribute__((used)) static void trb_to_noop(union xhci_trb *trb, u32 noop_type)
{
	if (trb_is_link(trb)) {
		/* unchain chained link TRBs */
		trb->link.control &= cpu_to_le32(~TRB_CHAIN);
	} else {
		trb->generic.field[0] = 0;
		trb->generic.field[1] = 0;
		trb->generic.field[2] = 0;
		/* Preserve only the cycle bit of this TRB */
		trb->generic.field[3] &= cpu_to_le32(TRB_CYCLE);
		trb->generic.field[3] |= cpu_to_le32(TRB_TYPE(noop_type));
	}
}