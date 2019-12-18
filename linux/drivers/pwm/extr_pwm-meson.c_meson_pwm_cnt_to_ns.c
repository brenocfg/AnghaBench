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
struct pwm_device {size_t hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct meson_pwm_channel {int pre_div; int /*<<< orphan*/  clk; } ;
struct meson_pwm {struct meson_pwm_channel* channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int div_u64 (int /*<<< orphan*/ ,unsigned long) ; 
 struct meson_pwm* to_meson_pwm (struct pwm_chip*) ; 

__attribute__((used)) static unsigned int meson_pwm_cnt_to_ns(struct pwm_chip *chip,
					struct pwm_device *pwm, u32 cnt)
{
	struct meson_pwm *meson = to_meson_pwm(chip);
	struct meson_pwm_channel *channel;
	unsigned long fin_freq;
	u32 fin_ns;

	/* to_meson_pwm() can only be used after .get_state() is called */
	channel = &meson->channels[pwm->hwpwm];

	fin_freq = clk_get_rate(channel->clk);
	if (fin_freq == 0)
		return 0;

	fin_ns = div_u64(NSEC_PER_SEC, fin_freq);

	return cnt * fin_ns * (channel->pre_div + 1);
}