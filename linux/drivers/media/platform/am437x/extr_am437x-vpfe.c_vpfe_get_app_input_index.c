#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vpfe_subdev_info {int /*<<< orphan*/  sd; } ;
struct vpfe_device {int current_input; struct vpfe_config* cfg; TYPE_1__* current_subdev; } ;
struct vpfe_config {struct vpfe_subdev_info* sub_devs; int /*<<< orphan*/  asd; } ;
struct i2c_client {scalar_t__ addr; TYPE_2__* adapter; } ;
struct TYPE_4__ {scalar_t__ nr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_get_app_input_index(struct vpfe_device *vpfe,
				    int *app_input_index)
{
	struct vpfe_config *cfg = vpfe->cfg;
	struct vpfe_subdev_info *sdinfo;
	struct i2c_client *client;
	struct i2c_client *curr_client;
	int i, j = 0;

	curr_client = v4l2_get_subdevdata(vpfe->current_subdev->sd);
	for (i = 0; i < ARRAY_SIZE(vpfe->cfg->asd); i++) {
		sdinfo = &cfg->sub_devs[i];
		client = v4l2_get_subdevdata(sdinfo->sd);
		if (client->addr == curr_client->addr &&
		    client->adapter->nr == curr_client->adapter->nr) {
			if (vpfe->current_input >= 1)
				return -1;
			*app_input_index = j + vpfe->current_input;
			return 0;
		}
		j++;
	}
	return -EINVAL;
}