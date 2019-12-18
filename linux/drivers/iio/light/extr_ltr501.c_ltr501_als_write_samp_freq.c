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
struct ltr501_data {int /*<<< orphan*/  lock_als; int /*<<< orphan*/  reg_als_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltr501_als_samp_table ; 
 int ltr501_match_samp_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ltr501_als_write_samp_freq(struct ltr501_data *data,
				      int val, int val2)
{
	int i, ret;

	i = ltr501_match_samp_freq(ltr501_als_samp_table,
				   ARRAY_SIZE(ltr501_als_samp_table),
				   val, val2);

	if (i < 0)
		return i;

	mutex_lock(&data->lock_als);
	ret = regmap_field_write(data->reg_als_rate, i);
	mutex_unlock(&data->lock_als);

	return ret;
}