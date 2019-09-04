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
struct vcnl4200_channel {int /*<<< orphan*/  reg; int /*<<< orphan*/  lock; int /*<<< orphan*/  last_measurement; int /*<<< orphan*/  sampling_rate; } ;
struct vcnl4000_data {int /*<<< orphan*/  client; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int vcnl4200_measure(struct vcnl4000_data *data,
		struct vcnl4200_channel *chan, int *val)
{
	int ret;
	s64 delta;
	ktime_t next_measurement;

	mutex_lock(&chan->lock);

	next_measurement = ktime_add(chan->last_measurement,
			chan->sampling_rate);
	delta = ktime_us_delta(next_measurement, ktime_get());
	if (delta > 0)
		usleep_range(delta, delta + 500);
	chan->last_measurement = ktime_get();

	mutex_unlock(&chan->lock);

	ret = i2c_smbus_read_word_data(data->client, chan->reg);
	if (ret < 0)
		return ret;

	*val = ret;

	return 0;
}