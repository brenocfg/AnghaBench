#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elan_tp_data {TYPE_2__* client; TYPE_1__* ops; int /*<<< orphan*/  vcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* power_control ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int ETP_RETRY_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static int elan_disable_power(struct elan_tp_data *data)
{
	int repeat = ETP_RETRY_COUNT;
	int error;

	do {
		error = data->ops->power_control(data->client, false);
		if (!error) {
			error = regulator_disable(data->vcc);
			if (error) {
				dev_err(&data->client->dev,
					"failed to disable regulator: %d\n",
					error);
				/* Attempt to power the chip back up */
				data->ops->power_control(data->client, true);
				break;
			}

			return 0;
		}

		msleep(30);
	} while (--repeat > 0);

	dev_err(&data->client->dev, "failed to disable power: %d\n", error);
	return error;
}