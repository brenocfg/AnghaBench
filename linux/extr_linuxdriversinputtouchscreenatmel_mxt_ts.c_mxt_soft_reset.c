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
struct mxt_data {int /*<<< orphan*/  reset_completion; int /*<<< orphan*/  irq; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXT_COMMAND_RESET ; 
 int /*<<< orphan*/  MXT_RESET_INVALID_CHG ; 
 int /*<<< orphan*/  MXT_RESET_TIMEOUT ; 
 int /*<<< orphan*/  MXT_RESET_VALUE ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxt_acquire_irq (struct mxt_data*) ; 
 int mxt_t6_command (struct mxt_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mxt_wait_for_completion (struct mxt_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxt_soft_reset(struct mxt_data *data)
{
	struct device *dev = &data->client->dev;
	int ret = 0;

	dev_info(dev, "Resetting device\n");

	disable_irq(data->irq);

	reinit_completion(&data->reset_completion);

	ret = mxt_t6_command(data, MXT_COMMAND_RESET, MXT_RESET_VALUE, false);
	if (ret)
		return ret;

	/* Ignore CHG line for 100ms after reset */
	msleep(MXT_RESET_INVALID_CHG);

	mxt_acquire_irq(data);

	ret = mxt_wait_for_completion(data, &data->reset_completion,
				      MXT_RESET_TIMEOUT);
	if (ret)
		return ret;

	return 0;
}