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
struct vpfe_device {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  asd; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 

__attribute__((used)) static int
vpfe_get_subdev_input_index(struct vpfe_device *vpfe,
			    int *subdev_index,
			    int *subdev_input_index,
			    int app_input_index)
{
	int i, j = 0;

	for (i = 0; i < ARRAY_SIZE(vpfe->cfg->asd); i++) {
		if (app_input_index < (j + 1)) {
			*subdev_index = i;
			*subdev_input_index = app_input_index - j;
			return 0;
		}
		j++;
	}
	return -EINVAL;
}