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
struct TYPE_3__ {int pll_current; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct bttv {int /*<<< orphan*/  tvnorm; int /*<<< orphan*/  input; TYPE_1__ pll; int /*<<< orphan*/  s_lock; scalar_t__ errors; TYPE_2__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_set_dma (struct bttv*,int /*<<< orphan*/ ) ; 
 scalar_t__ bttv_verbose ; 
 int /*<<< orphan*/  init_bt848 (struct bttv*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bttv_reinit_bt848(struct bttv *btv)
{
	unsigned long flags;

	if (bttv_verbose)
		pr_info("%d: reset, reinitialize\n", btv->c.nr);
	spin_lock_irqsave(&btv->s_lock,flags);
	btv->errors=0;
	bttv_set_dma(btv,0);
	spin_unlock_irqrestore(&btv->s_lock,flags);

	init_bt848(btv);
	btv->pll.pll_current = -1;
	set_input(btv, btv->input, btv->tvnorm);
}