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
struct lm95245_data {long interval; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM95245_REG_RW_CONVERS_RATE ; 
 int RATE_CR0063 ; 
 int RATE_CR0364 ; 
 int RATE_CR1000 ; 
 int RATE_CR2500 ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm95245_set_conversion_rate(struct lm95245_data *data, long interval)
{
	int ret, rate;

	if (interval <= 63) {
		interval = 63;
		rate = RATE_CR0063;
	} else if (interval <= 364) {
		interval = 364;
		rate = RATE_CR0364;
	} else if (interval <= 1000) {
		interval = 1000;
		rate = RATE_CR1000;
	} else {
		interval = 2500;
		rate = RATE_CR2500;
	}

	ret = regmap_write(data->regmap, LM95245_REG_RW_CONVERS_RATE, rate);
	if (ret < 0)
		return ret;

	data->interval = interval;
	return 0;
}