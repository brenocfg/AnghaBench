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
struct TYPE_3__ {int step_width; int step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {scalar_t__ index; scalar_t__ pixel_format; TYPE_1__ stepwise; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int N_VIA_FMTS ; 
 int /*<<< orphan*/  QCIF_HEIGHT ; 
 int /*<<< orphan*/  QCIF_WIDTH ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  VGA_HEIGHT ; 
 int /*<<< orphan*/  VGA_WIDTH ; 
 TYPE_2__* via_formats ; 

__attribute__((used)) static int viacam_enum_framesizes(struct file *filp, void *priv,
		struct v4l2_frmsizeenum *sizes)
{
	unsigned int i;

	if (sizes->index != 0)
		return -EINVAL;
	for (i = 0; i < N_VIA_FMTS; i++)
		if (sizes->pixel_format == via_formats[i].pixelformat)
			break;
	if (i >= N_VIA_FMTS)
		return -EINVAL;
	sizes->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	sizes->stepwise.min_width = QCIF_WIDTH;
	sizes->stepwise.min_height = QCIF_HEIGHT;
	sizes->stepwise.max_width = VGA_WIDTH;
	sizes->stepwise.max_height = VGA_HEIGHT;
	sizes->stepwise.step_width = sizes->stepwise.step_height = 1;
	return 0;
}