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
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {int /*<<< orphan*/  resolution; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARM_MON_FPS ; 
 int /*<<< orphan*/  PARM_MON_SIZE ; 
 int /*<<< orphan*/  REG_FPS_30 ; 
 int /*<<< orphan*/  REG_MONITOR ; 
 int /*<<< orphan*/  REG_PARAMETER ; 
 int m5mols_restore_controls (struct m5mols_info*) ; 
 int m5mols_set_mode (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int m5mols_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m5mols_start_monitor(struct m5mols_info *info)
{
	struct v4l2_subdev *sd = &info->sd;
	int ret;

	ret = m5mols_set_mode(info, REG_PARAMETER);
	if (!ret)
		ret = m5mols_write(sd, PARM_MON_SIZE, info->resolution);
	if (!ret)
		ret = m5mols_write(sd, PARM_MON_FPS, REG_FPS_30);
	if (!ret)
		ret = m5mols_set_mode(info, REG_MONITOR);
	if (!ret)
		ret = m5mols_restore_controls(info);

	return ret;
}