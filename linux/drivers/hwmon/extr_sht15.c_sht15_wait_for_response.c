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
struct sht15_data {int /*<<< orphan*/  sck; int /*<<< orphan*/  dev; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SHT15_TSCKH ; 
 int /*<<< orphan*/  SHT15_TSCKL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int sht15_connection_reset (struct sht15_data*) ; 

__attribute__((used)) static int sht15_wait_for_response(struct sht15_data *data)
{
	int err;

	err = gpiod_direction_input(data->data);
	if (err)
		return err;
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	if (gpiod_get_value(data->data)) {
		gpiod_set_value(data->sck, 0);
		dev_err(data->dev, "Command not acknowledged\n");
		err = sht15_connection_reset(data);
		if (err)
			return err;
		return -EIO;
	}
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	return 0;
}