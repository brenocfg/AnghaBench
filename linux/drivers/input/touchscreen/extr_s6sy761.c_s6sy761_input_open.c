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
struct s6sy761_data {int /*<<< orphan*/  client; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S6SY761_SENSE_ON ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s6sy761_data* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int s6sy761_input_open(struct input_dev *dev)
{
	struct s6sy761_data *sdata = input_get_drvdata(dev);

	return i2c_smbus_write_byte(sdata->client, S6SY761_SENSE_ON);
}