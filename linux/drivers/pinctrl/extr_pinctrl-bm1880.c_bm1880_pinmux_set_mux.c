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
typedef  int u32 ;
struct pinctrl_dev {int dummy; } ;
struct bm1880_pinmux_function {int mux_val; } ;
struct bm1880_pinctrl {int base; struct bm1880_pinmux_function* funcs; struct bm1880_pctrl_group* groups; } ;
struct bm1880_pctrl_group {int npins; unsigned int* pins; } ;

/* Variables and functions */
 int BM1880_REG_MUX ; 
 struct bm1880_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl_relaxed (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,int) ; 

__attribute__((used)) static int bm1880_pinmux_set_mux(struct pinctrl_dev *pctldev,
				 unsigned int function,
				 unsigned int  group)
{
	struct bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	const struct bm1880_pctrl_group *pgrp = &pctrl->groups[group];
	const struct bm1880_pinmux_function *func = &pctrl->funcs[function];
	int i;

	for (i = 0; i < pgrp->npins; i++) {
		unsigned int pin = pgrp->pins[i];
		u32 offset = (pin >> 1) << 2;
		u32 mux_offset = ((!((pin + 1) & 1) << 4) + 4);
		u32 regval = readl_relaxed(pctrl->base + BM1880_REG_MUX +
					   offset);

		regval &= ~(0x03 << mux_offset);
		regval |= func->mux_val << mux_offset;

		writel_relaxed(regval, pctrl->base + BM1880_REG_MUX + offset);
	}

	return 0;
}