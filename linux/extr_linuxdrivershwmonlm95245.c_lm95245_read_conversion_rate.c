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
struct lm95245_data {int interval; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM95245_REG_RW_CONVERS_RATE ; 
#define  RATE_CR0063 131 
#define  RATE_CR0364 130 
#define  RATE_CR1000 129 
#define  RATE_CR2500 128 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int lm95245_read_conversion_rate(struct lm95245_data *data)
{
	unsigned int rate;
	int ret;

	ret = regmap_read(data->regmap, LM95245_REG_RW_CONVERS_RATE, &rate);
	if (ret < 0)
		return ret;

	switch (rate) {
	case RATE_CR0063:
		data->interval = 63;
		break;
	case RATE_CR0364:
		data->interval = 364;
		break;
	case RATE_CR1000:
		data->interval = 1000;
		break;
	case RATE_CR2500:
	default:
		data->interval = 2500;
		break;
	}
	return 0;
}