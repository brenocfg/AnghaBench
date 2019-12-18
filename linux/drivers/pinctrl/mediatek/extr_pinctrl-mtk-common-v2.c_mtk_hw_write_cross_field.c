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
struct mtk_pinctrl {int dummy; } ;
struct mtk_pin_field {int mask; int bitpos; scalar_t__ next; scalar_t__ offset; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  mtk_hw_bits_part (struct mtk_pin_field*,int*,int*) ; 
 int /*<<< orphan*/  mtk_rmw (struct mtk_pinctrl*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void mtk_hw_write_cross_field(struct mtk_pinctrl *hw,
				     struct mtk_pin_field *pf, int value)
{
	int nbits_l, nbits_h;

	mtk_hw_bits_part(pf, &nbits_h, &nbits_l);

	mtk_rmw(hw, pf->index, pf->offset, pf->mask << pf->bitpos,
		(value & pf->mask) << pf->bitpos);

	mtk_rmw(hw, pf->index, pf->offset + pf->next, BIT(nbits_h) - 1,
		(value & pf->mask) >> nbits_l);
}