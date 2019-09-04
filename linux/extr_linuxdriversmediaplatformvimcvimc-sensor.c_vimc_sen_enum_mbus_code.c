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
struct vimc_pix_map {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int /*<<< orphan*/  code; int /*<<< orphan*/  index; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vimc_pix_map* vimc_pix_map_by_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vimc_sen_enum_mbus_code(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_mbus_code_enum *code)
{
	const struct vimc_pix_map *vpix = vimc_pix_map_by_index(code->index);

	if (!vpix)
		return -EINVAL;

	code->code = vpix->code;

	return 0;
}