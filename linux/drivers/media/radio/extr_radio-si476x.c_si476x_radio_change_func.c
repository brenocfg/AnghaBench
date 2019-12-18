#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct si476x_radio {TYPE_2__* core; } ;
typedef  enum si476x_func { ____Placeholder_si476x_func } si476x_func ;
struct TYPE_4__ {int func; } ;
struct TYPE_5__ {TYPE_1__ power_up_parameters; } ;

/* Variables and functions */
 int SI476X_FUNC_AM_RECEIVER ; 
 int SI476X_FUNC_FM_RECEIVER ; 
 int si476x_core_start (TYPE_2__*,int) ; 
 int si476x_core_stop (TYPE_2__*,int) ; 
 int si476x_radio_do_post_powerup_init (struct si476x_radio*,int) ; 

__attribute__((used)) static int si476x_radio_change_func(struct si476x_radio *radio,
				    enum si476x_func func)
{
	int err;
	bool soft;
	/*
	 * Since power/up down is a very time consuming operation,
	 * try to avoid doing it if the requested mode matches the one
	 * the tuner is in
	 */
	if (func == radio->core->power_up_parameters.func)
		return 0;

	soft = true;
	err = si476x_core_stop(radio->core, soft);
	if (err < 0) {
		/*
		 * OK, if the chip does not want to play nice let's
		 * try to reset it in more brutal way
		 */
		soft = false;
		err = si476x_core_stop(radio->core, soft);
		if (err < 0)
			return err;
	}
	/*
	  Set the desired radio tuner function
	 */
	radio->core->power_up_parameters.func = func;

	err = si476x_core_start(radio->core, soft);
	if (err < 0)
		return err;

	/*
	 * No need to do the rest of manipulations for the bootlader
	 * mode
	 */
	if (func != SI476X_FUNC_FM_RECEIVER &&
	    func != SI476X_FUNC_AM_RECEIVER)
		return err;

	return si476x_radio_do_post_powerup_init(radio, func);
}