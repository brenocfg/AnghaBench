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
struct bma180_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ bma180_set_ee_writing_state (struct bma180_data*,int) ; 
 scalar_t__ bma180_set_new_data_intr_state (struct bma180_data*,int) ; 
 scalar_t__ bma180_set_sleep_state (struct bma180_data*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void bma180_chip_disable(struct bma180_data *data)
{
	if (bma180_set_new_data_intr_state(data, false))
		goto err;
	if (bma180_set_ee_writing_state(data, false))
		goto err;
	if (bma180_set_sleep_state(data, true))
		goto err;

	return;

err:
	dev_err(&data->client->dev, "failed to disable the chip\n");
}