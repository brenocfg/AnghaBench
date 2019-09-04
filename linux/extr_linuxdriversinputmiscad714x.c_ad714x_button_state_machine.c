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
struct ad714x_chip {int h_state; int l_state; int /*<<< orphan*/  dev; TYPE_2__* sw; TYPE_1__* hw; } ;
struct ad714x_button_plat {int h_mask; int l_mask; int /*<<< orphan*/  keycode; } ;
struct ad714x_button_drv {int state; int /*<<< orphan*/  input; } ;
struct TYPE_4__ {struct ad714x_button_drv* button; } ;
struct TYPE_3__ {struct ad714x_button_plat* button; } ;

/* Variables and functions */
#define  ACTIVE 129 
#define  IDLE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad714x_button_state_machine(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_button_plat *hw = &ad714x->hw->button[idx];
	struct ad714x_button_drv *sw = &ad714x->sw->button[idx];

	switch (sw->state) {
	case IDLE:
		if (((ad714x->h_state & hw->h_mask) == hw->h_mask) &&
		    ((ad714x->l_state & hw->l_mask) == hw->l_mask)) {
			dev_dbg(ad714x->dev, "button %d touched\n", idx);
			input_report_key(sw->input, hw->keycode, 1);
			input_sync(sw->input);
			sw->state = ACTIVE;
		}
		break;

	case ACTIVE:
		if (((ad714x->h_state & hw->h_mask) != hw->h_mask) ||
		    ((ad714x->l_state & hw->l_mask) != hw->l_mask)) {
			dev_dbg(ad714x->dev, "button %d released\n", idx);
			input_report_key(sw->input, hw->keycode, 0);
			input_sync(sw->input);
			sw->state = IDLE;
		}
		break;

	default:
		break;
	}
}