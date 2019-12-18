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
struct TYPE_4__ {int mute; int /*<<< orphan*/ * ops; struct bttv* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct bttv {scalar_t__ has_radio; scalar_t__ has_tea575x; TYPE_2__ tea; TYPE_1__ c; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  bttv_tea_ops ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_tea575x_hw_init (TYPE_2__*) ; 

__attribute__((used)) static int tea575x_init(struct bttv *btv)
{
	btv->tea.private_data = btv;
	btv->tea.ops = &bttv_tea_ops;
	if (!snd_tea575x_hw_init(&btv->tea)) {
		pr_info("%d: detected TEA575x radio\n", btv->c.nr);
		btv->tea.mute = false;
		return 0;
	}

	btv->has_tea575x = 0;
	btv->has_radio = 0;

	return -ENODEV;
}