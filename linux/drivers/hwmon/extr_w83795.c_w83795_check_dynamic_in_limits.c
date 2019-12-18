#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct w83795_data {int has_dyn_in; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {TYPE_1__ dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  W83795_REG_VID_CTRL ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int,int,int) ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 int sysfs_chmod_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__** w83795_in ; 
 int w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w83795_check_dynamic_in_limits(struct i2c_client *client)
{
	struct w83795_data *data = i2c_get_clientdata(client);
	u8 vid_ctl;
	int i, err_max, err_min;

	vid_ctl = w83795_read(client, W83795_REG_VID_CTRL);

	/* Return immediately if VRM isn't configured */
	if ((vid_ctl & 0x07) == 0x00 || (vid_ctl & 0x07) == 0x07)
		return;

	data->has_dyn_in = (vid_ctl >> 3) & 0x07;
	for (i = 0; i < 2; i++) {
		if (!(data->has_dyn_in & (1 << i)))
			continue;

		/* Voltage limits in dynamic mode, switch to read-only */
		err_max = sysfs_chmod_file(&client->dev.kobj,
					   &w83795_in[i][2].dev_attr.attr,
					   S_IRUGO);
		err_min = sysfs_chmod_file(&client->dev.kobj,
					   &w83795_in[i][3].dev_attr.attr,
					   S_IRUGO);
		if (err_max || err_min)
			dev_warn(&client->dev,
				 "Failed to set in%d limits read-only (%d, %d)\n",
				 i, err_max, err_min);
		else
			dev_info(&client->dev,
				 "in%d limits set dynamically from VID\n", i);
	}
}