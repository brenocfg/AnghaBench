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
struct lm3533_platform_data {int /*<<< orphan*/  boost_ovp; int /*<<< orphan*/  boost_freq; } ;
struct lm3533 {int dummy; } ;

/* Variables and functions */
 int lm3533_set_boost_freq (struct lm3533*,int /*<<< orphan*/ ) ; 
 int lm3533_set_boost_ovp (struct lm3533*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3533_device_setup(struct lm3533 *lm3533,
					struct lm3533_platform_data *pdata)
{
	int ret;

	ret = lm3533_set_boost_freq(lm3533, pdata->boost_freq);
	if (ret)
		return ret;

	return lm3533_set_boost_ovp(lm3533, pdata->boost_ovp);
}