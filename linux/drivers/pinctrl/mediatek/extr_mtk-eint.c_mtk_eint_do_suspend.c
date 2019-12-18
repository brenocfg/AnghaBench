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
struct mtk_eint {int /*<<< orphan*/  wake_mask; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_eint_chip_write_mask (struct mtk_eint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mtk_eint_do_suspend(struct mtk_eint *eint)
{
	mtk_eint_chip_write_mask(eint, eint->base, eint->wake_mask);

	return 0;
}