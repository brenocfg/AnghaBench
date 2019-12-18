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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  status; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct tw686x_video_channel {size_t ch; int /*<<< orphan*/  dev; TYPE_1__* device; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TW686X_INPUTS_PER_CH ; 
 unsigned int TW686X_VIDSTAT_HLOCK ; 
 unsigned int TW686X_VIDSTAT_VDLOSS ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_CAP_STD ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_H_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int /*<<< orphan*/ * VIDSTAT ; 
 unsigned int reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 struct tw686x_video_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw686x_enum_input(struct file *file, void *priv,
			     struct v4l2_input *i)
{
	struct tw686x_video_channel *vc = video_drvdata(file);
	unsigned int vidstat;

	if (i->index >= TW686X_INPUTS_PER_CH)
		return -EINVAL;

	snprintf(i->name, sizeof(i->name), "Composite%d", i->index);
	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = vc->device->tvnorms;
	i->capabilities = V4L2_IN_CAP_STD;

	vidstat = reg_read(vc->dev, VIDSTAT[vc->ch]);
	i->status = 0;
	if (vidstat & TW686X_VIDSTAT_VDLOSS)
		i->status |= V4L2_IN_ST_NO_SIGNAL;
	if (!(vidstat & TW686X_VIDSTAT_HLOCK))
		i->status |= V4L2_IN_ST_NO_H_LOCK;

	return 0;
}