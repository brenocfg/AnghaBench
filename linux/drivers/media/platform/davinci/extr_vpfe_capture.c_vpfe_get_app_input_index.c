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
struct vpfe_subdev_info {int num_inputs; int /*<<< orphan*/  name; } ;
struct vpfe_device {int current_input; TYPE_1__* current_subdev; struct vpfe_config* cfg; } ;
struct vpfe_config {int num_subdevs; struct vpfe_subdev_info* sub_devs; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_get_app_input_index(struct vpfe_device *vpfe_dev,
				    int *app_input_index)
{
	struct vpfe_config *cfg = vpfe_dev->cfg;
	struct vpfe_subdev_info *sdinfo;
	int i, j = 0;

	for (i = 0; i < cfg->num_subdevs; i++) {
		sdinfo = &cfg->sub_devs[i];
		if (!strcmp(sdinfo->name, vpfe_dev->current_subdev->name)) {
			if (vpfe_dev->current_input >= sdinfo->num_inputs)
				return -1;
			*app_input_index = j + vpfe_dev->current_input;
			return 0;
		}
		j += sdinfo->num_inputs;
	}
	return -EINVAL;
}