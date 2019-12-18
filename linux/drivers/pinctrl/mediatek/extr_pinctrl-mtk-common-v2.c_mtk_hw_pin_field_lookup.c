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
typedef  int u32 ;
struct mtk_pinctrl {int nbase; int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct mtk_pin_reg_calc {int nranges; struct mtk_pin_field_calc* range; } ;
struct mtk_pin_field_calc {scalar_t__ s_pin; scalar_t__ e_pin; int i_base; int s_bit; int x_bits; int x_addrs; int sz_reg; scalar_t__ s_addr; scalar_t__ fixed; } ;
struct mtk_pin_field {int index; int bitpos; int mask; int next; scalar_t__ offset; } ;
struct mtk_pin_desc {scalar_t__ number; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct mtk_pin_reg_calc* reg_cal; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hw_pin_field_lookup(struct mtk_pinctrl *hw,
				   const struct mtk_pin_desc *desc,
				   int field, struct mtk_pin_field *pfd)
{
	const struct mtk_pin_field_calc *c, *e;
	const struct mtk_pin_reg_calc *rc;
	u32 bits;

	if (hw->soc->reg_cal && hw->soc->reg_cal[field].range) {
		rc = &hw->soc->reg_cal[field];
	} else {
		dev_dbg(hw->dev,
			"Not support field %d for pin %d (%s)\n",
			field, desc->number, desc->name);
		return -ENOTSUPP;
	}

	c = rc->range;
	e = c + rc->nranges;

	while (c < e) {
		if (desc->number >= c->s_pin && desc->number <= c->e_pin)
			break;
		c++;
	}

	if (c >= e) {
		dev_dbg(hw->dev, "Not support field %d for pin = %d (%s)\n",
			field, desc->number, desc->name);
		return -ENOTSUPP;
	}

	if (c->i_base > hw->nbase - 1) {
		dev_err(hw->dev,
			"Invalid base for field %d for pin = %d (%s)\n",
			field, desc->number, desc->name);
		return -EINVAL;
	}

	/* Calculated bits as the overall offset the pin is located at,
	 * if c->fixed is held, that determines the all the pins in the
	 * range use the same field with the s_pin.
	 */
	bits = c->fixed ? c->s_bit : c->s_bit +
	       (desc->number - c->s_pin) * (c->x_bits);

	/* Fill pfd from bits. For example 32-bit register applied is assumed
	 * when c->sz_reg is equal to 32.
	 */
	pfd->index = c->i_base;
	pfd->offset = c->s_addr + c->x_addrs * (bits / c->sz_reg);
	pfd->bitpos = bits % c->sz_reg;
	pfd->mask = (1 << c->x_bits) - 1;

	/* pfd->next is used for indicating that bit wrapping-around happens
	 * which requires the manipulation for bit 0 starting in the next
	 * register to form the complete field read/write.
	 */
	pfd->next = pfd->bitpos + c->x_bits > c->sz_reg ? c->x_addrs : 0;

	return 0;
}