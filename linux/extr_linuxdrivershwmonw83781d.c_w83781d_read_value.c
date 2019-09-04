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
typedef  int /*<<< orphan*/  u16 ;
struct w83781d_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w83781d_read_value_i2c (struct w83781d_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
w83781d_read_value(struct w83781d_data *data, u16 reg)
{
	int res;

	mutex_lock(&data->lock);
	res = w83781d_read_value_i2c(data, reg);
	mutex_unlock(&data->lock);

	return res;
}