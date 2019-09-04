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
struct ad714x_touchpad_plat {int /*<<< orphan*/  x_end_stage; int /*<<< orphan*/  x_start_stage; } ;
struct ad714x_chip {TYPE_1__* hw; } ;
struct TYPE_2__ {struct ad714x_touchpad_plat* touchpad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad714x_use_com_int (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void touchpad_use_com_int(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];

	ad714x_use_com_int(ad714x, hw->x_start_stage, hw->x_end_stage);
}