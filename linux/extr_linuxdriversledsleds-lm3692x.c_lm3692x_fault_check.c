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
struct lm3692x_led {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3692X_FAULT_FLAGS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int lm3692x_fault_check(struct lm3692x_led *led)
{
	int ret;
	unsigned int read_buf;

	ret = regmap_read(led->regmap, LM3692X_FAULT_FLAGS, &read_buf);
	if (ret)
		return ret;

	if (read_buf)
		dev_err(&led->client->dev, "Detected a fault 0x%X\n", read_buf);

	/* The first read may clear the fault.  Check again to see if the fault
	 * still exits and return that value.
	 */
	regmap_read(led->regmap, LM3692X_FAULT_FLAGS, &read_buf);
	if (read_buf)
		dev_err(&led->client->dev, "Second read of fault flags 0x%X\n",
			read_buf);

	return read_buf;
}