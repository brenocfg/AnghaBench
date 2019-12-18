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
struct timer_list {int dummy; } ;
struct pwrkey_drv_data {int keystate; int /*<<< orphan*/  check_timer; struct input_dev* input; int /*<<< orphan*/  keycode; int /*<<< orphan*/  snvs; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  REPEAT_INTERVAL ; 
 int SNVS_HPSR_BTN ; 
 int /*<<< orphan*/  SNVS_HPSR_REG ; 
 int /*<<< orphan*/  check_timer ; 
 struct pwrkey_drv_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct pwrkey_drv_data* pdata ; 
 int /*<<< orphan*/  pm_relax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void imx_imx_snvs_check_for_events(struct timer_list *t)
{
	struct pwrkey_drv_data *pdata = from_timer(pdata, t, check_timer);
	struct input_dev *input = pdata->input;
	u32 state;

	regmap_read(pdata->snvs, SNVS_HPSR_REG, &state);
	state = state & SNVS_HPSR_BTN ? 1 : 0;

	/* only report new event if status changed */
	if (state ^ pdata->keystate) {
		pdata->keystate = state;
		input_event(input, EV_KEY, pdata->keycode, state);
		input_sync(input);
		pm_relax(pdata->input->dev.parent);
	}

	/* repeat check if pressed long */
	if (state) {
		mod_timer(&pdata->check_timer,
			  jiffies + msecs_to_jiffies(REPEAT_INTERVAL));
	}
}