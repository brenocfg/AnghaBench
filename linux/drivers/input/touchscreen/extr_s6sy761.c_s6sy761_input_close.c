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
struct s6sy761_data {TYPE_1__* client; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S6SY761_SENSE_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct s6sy761_data* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void s6sy761_input_close(struct input_dev *dev)
{
	struct s6sy761_data *sdata = input_get_drvdata(dev);
	int ret;

	ret = i2c_smbus_write_byte(sdata->client, S6SY761_SENSE_OFF);
	if (ret)
		dev_err(&sdata->client->dev, "failed to turn off sensing\n");
}