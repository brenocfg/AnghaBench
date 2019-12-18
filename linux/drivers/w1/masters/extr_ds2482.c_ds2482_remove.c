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
struct i2c_client {int dummy; } ;
struct ds2482_data {int w1_count; TYPE_1__* w1_ch; } ;
struct TYPE_2__ {int /*<<< orphan*/  w1_bm; int /*<<< orphan*/ * pdev; } ;

/* Variables and functions */
 struct ds2482_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct ds2482_data*) ; 
 int /*<<< orphan*/  w1_remove_master_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds2482_remove(struct i2c_client *client)
{
	struct ds2482_data   *data = i2c_get_clientdata(client);
	int idx;

	/* Unregister the 1-wire bridge(s) */
	for (idx = 0; idx < data->w1_count; idx++) {
		if (data->w1_ch[idx].pdev != NULL)
			w1_remove_master_device(&data->w1_ch[idx].w1_bm);
	}

	/* Free the memory */
	kfree(data);
	return 0;
}