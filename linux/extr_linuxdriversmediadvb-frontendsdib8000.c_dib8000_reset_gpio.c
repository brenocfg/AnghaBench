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
struct TYPE_2__ {int /*<<< orphan*/  pwm_freq_div; int /*<<< orphan*/  gpio_pwm_pos; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_dir; } ;
struct dib8000_state {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib8000_reset_gpio(struct dib8000_state *st)
{
	/* reset the GPIOs */
	dib8000_write_word(st, 1029, st->cfg.gpio_dir);
	dib8000_write_word(st, 1030, st->cfg.gpio_val);

	/* TODO 782 is P_gpio_od */

	dib8000_write_word(st, 1032, st->cfg.gpio_pwm_pos);

	dib8000_write_word(st, 1037, st->cfg.pwm_freq_div);
	return 0;
}