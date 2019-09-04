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
struct TYPE_4__ {int /*<<< orphan*/  phys; } ;
struct TYPE_3__ {int /*<<< orphan*/  dscr; } ;
struct at_desc {int /*<<< orphan*/  tx_list; int /*<<< orphan*/  desc_node; TYPE_2__ txd; TYPE_1__ lli; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atc_desc_chain(struct at_desc **first, struct at_desc **prev,
			   struct at_desc *desc)
{
	if (!(*first)) {
		*first = desc;
	} else {
		/* inform the HW lli about chaining */
		(*prev)->lli.dscr = desc->txd.phys;
		/* insert the link descriptor to the LD ring */
		list_add_tail(&desc->desc_node,
				&(*first)->tx_list);
	}
	*prev = desc;
}