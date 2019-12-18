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
struct lmp91000_data {int chan_select; int* buffer; int /*<<< orphan*/  completion; int /*<<< orphan*/  trig; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  LMP91000_REG_MODECN ; 
 int LMP91000_REG_MODECN_3LEAD ; 
 int LMP91000_REG_MODECN_TEMP ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lmp91000_read(struct lmp91000_data *data, int channel, int *val)
{
	int state, ret;

	ret = regmap_read(data->regmap, LMP91000_REG_MODECN, &state);
	if (ret)
		return -EINVAL;

	ret = regmap_write(data->regmap, LMP91000_REG_MODECN, channel);
	if (ret)
		return -EINVAL;

	/* delay till first temperature reading is complete */
	if (state != channel && channel == LMP91000_REG_MODECN_TEMP)
		usleep_range(3000, 4000);

	data->chan_select = channel != LMP91000_REG_MODECN_3LEAD;

	iio_trigger_poll_chained(data->trig);

	ret = wait_for_completion_timeout(&data->completion, HZ);
	reinit_completion(&data->completion);

	if (!ret)
		return -ETIMEDOUT;

	*val = data->buffer[data->chan_select];

	return 0;
}