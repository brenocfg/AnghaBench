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
struct lp8860_led {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8860_CLEAR_FAULTS ; 
 int /*<<< orphan*/  LP8860_FAULT ; 
 int /*<<< orphan*/  LP8860_FAULT_CLEAR ; 
 int /*<<< orphan*/  LP8860_LED_FAULT ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8860_fault_check(struct lp8860_led *led)
{
	int ret, fault;
	unsigned int read_buf;

	ret = regmap_read(led->regmap, LP8860_LED_FAULT, &read_buf);
	if (ret)
		goto out;

	fault = read_buf;

	ret = regmap_read(led->regmap, LP8860_FAULT, &read_buf);
	if (ret)
		goto out;

	fault |= read_buf;

	/* Attempt to clear any faults */
	if (fault)
		ret = regmap_write(led->regmap, LP8860_FAULT_CLEAR,
			LP8860_CLEAR_FAULTS);
out:
	return ret;
}