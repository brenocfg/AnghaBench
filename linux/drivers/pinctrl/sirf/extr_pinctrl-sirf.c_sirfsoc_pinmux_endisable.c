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
struct sirfsoc_pmx {scalar_t__ rsc_virtbase; scalar_t__ gpio_virtbase; } ;
struct sirfsoc_padmux {int muxmask_counts; int funcmask; int funcval; scalar_t__ ctrlreg; struct sirfsoc_muxmask* muxmask; } ;
struct sirfsoc_muxmask {int mask; int /*<<< orphan*/  group; } ;
struct TYPE_2__ {struct sirfsoc_padmux* padmux; } ;

/* Variables and functions */
 scalar_t__ SIRFSOC_GPIO_PAD_EN (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 TYPE_1__* sirfsoc_pmx_functions ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sirfsoc_pinmux_endisable(struct sirfsoc_pmx *spmx,
					unsigned selector, bool enable)
{
	int i;
	const struct sirfsoc_padmux *mux =
		sirfsoc_pmx_functions[selector].padmux;
	const struct sirfsoc_muxmask *mask = mux->muxmask;

	for (i = 0; i < mux->muxmask_counts; i++) {
		u32 muxval;
		muxval = readl(spmx->gpio_virtbase +
			SIRFSOC_GPIO_PAD_EN(mask[i].group));
		if (enable)
			muxval = muxval & ~mask[i].mask;
		else
			muxval = muxval | mask[i].mask;
		writel(muxval, spmx->gpio_virtbase +
			SIRFSOC_GPIO_PAD_EN(mask[i].group));
	}

	if (mux->funcmask && enable) {
		u32 func_en_val;

		func_en_val =
			readl(spmx->rsc_virtbase + mux->ctrlreg);
		func_en_val =
			(func_en_val & ~mux->funcmask) | (mux->funcval);
		writel(func_en_val, spmx->rsc_virtbase + mux->ctrlreg);
	}
}