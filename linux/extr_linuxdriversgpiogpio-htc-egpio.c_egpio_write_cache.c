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
struct egpio_info {int nchips; int reg_shift; int reg_mask; struct egpio_chip* chip; } ;
struct TYPE_2__ {int ngpio; } ;
struct egpio_chip {int is_out; int reg_start; int cached_values; TYPE_1__ chip; } ;

/* Variables and functions */
 int egpio_pos (struct egpio_info*,int) ; 
 int /*<<< orphan*/  egpio_readw (struct egpio_info*,int) ; 
 int /*<<< orphan*/  egpio_writew (int,struct egpio_info*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void egpio_write_cache(struct egpio_info *ei)
{
	int               i;
	struct egpio_chip *egpio;
	int               shift;

	for (i = 0; i < ei->nchips; i++) {
		egpio = &(ei->chip[i]);
		if (!egpio->is_out)
			continue;

		for (shift = 0; shift < egpio->chip.ngpio;
				shift += (1<<ei->reg_shift)) {

			int reg = egpio->reg_start + egpio_pos(ei, shift);

			if (!((egpio->is_out >> shift) & ei->reg_mask))
				continue;

			pr_debug("EGPIO: setting %x to %x, was %x\n", reg,
				(egpio->cached_values >> shift) & ei->reg_mask,
				egpio_readw(ei, reg));

			egpio_writew((egpio->cached_values >> shift)
					& ei->reg_mask, ei, reg);
		}
	}
}