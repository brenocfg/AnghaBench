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
struct device {int dummy; } ;
struct da9063_compatible_rtc_regmap {int /*<<< orphan*/  rtc_alarm_on_mask; int /*<<< orphan*/  rtc_alarm_year_reg; } ;
struct da9063_compatible_rtc {int /*<<< orphan*/  regmap; struct da9063_compatible_rtc_regmap* config; } ;

/* Variables and functions */
 struct da9063_compatible_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9063_rtc_start_alarm(struct device *dev)
{
	struct da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	const struct da9063_compatible_rtc_regmap *config = rtc->config;

	return regmap_update_bits(rtc->regmap,
				  config->rtc_alarm_year_reg,
				  config->rtc_alarm_on_mask,
				  config->rtc_alarm_on_mask);
}