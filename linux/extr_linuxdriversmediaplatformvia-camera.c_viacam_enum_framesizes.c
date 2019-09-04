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
struct TYPE_2__ {int step_width; int step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {scalar_t__ index; TYPE_1__ stepwise; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QCIF_HEIGHT ; 
 int /*<<< orphan*/  QCIF_WIDTH ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  VGA_HEIGHT ; 
 int /*<<< orphan*/  VGA_WIDTH ; 

__attribute__((used)) static int viacam_enum_framesizes(struct file *filp, void *priv,
		struct v4l2_frmsizeenum *sizes)
{
	if (sizes->index != 0)
		return -EINVAL;
	sizes->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	sizes->stepwise.min_width = QCIF_WIDTH;
	sizes->stepwise.min_height = QCIF_HEIGHT;
	sizes->stepwise.max_width = VGA_WIDTH;
	sizes->stepwise.max_height = VGA_HEIGHT;
	sizes->stepwise.step_width = sizes->stepwise.step_height = 1;
	return 0;
}