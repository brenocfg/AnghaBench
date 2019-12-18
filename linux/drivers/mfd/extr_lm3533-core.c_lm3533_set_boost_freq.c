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
struct lm3533 {int /*<<< orphan*/  dev; } ;
typedef  enum lm3533_boost_freq { ____Placeholder_lm3533_boost_freq } lm3533_boost_freq ;

/* Variables and functions */
 int /*<<< orphan*/  LM3533_BOOST_FREQ_MASK ; 
 int LM3533_BOOST_FREQ_SHIFT ; 
 int /*<<< orphan*/  LM3533_REG_BOOST_PWM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lm3533_update (struct lm3533*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3533_set_boost_freq(struct lm3533 *lm3533,
						enum lm3533_boost_freq freq)
{
	int ret;

	ret = lm3533_update(lm3533, LM3533_REG_BOOST_PWM,
					freq << LM3533_BOOST_FREQ_SHIFT,
					LM3533_BOOST_FREQ_MASK);
	if (ret)
		dev_err(lm3533->dev, "failed to set boost frequency\n");

	return ret;
}