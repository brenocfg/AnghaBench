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
struct vz89x_data {int is_valid; int (* xfer ) (struct vz89x_data*,int /*<<< orphan*/ ) ;scalar_t__ last_update; struct vz89x_chip_data* chip; } ;
struct vz89x_chip_data {int (* valid ) (struct vz89x_data*) ;int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ HZ ; 
 scalar_t__ jiffies ; 
 int stub1 (struct vz89x_data*,int /*<<< orphan*/ ) ; 
 int stub2 (struct vz89x_data*) ; 
 int /*<<< orphan*/  time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int vz89x_get_measurement(struct vz89x_data *data)
{
	const struct vz89x_chip_data *chip = data->chip;
	int ret;

	/* sensor can only be polled once a second max per datasheet */
	if (!time_after(jiffies, data->last_update + HZ))
		return data->is_valid ? 0 : -EAGAIN;

	data->is_valid = false;
	data->last_update = jiffies;

	ret = data->xfer(data, chip->cmd);
	if (ret < 0)
		return ret;

	ret = chip->valid(data);
	if (ret)
		return -EAGAIN;

	data->is_valid = true;

	return 0;
}