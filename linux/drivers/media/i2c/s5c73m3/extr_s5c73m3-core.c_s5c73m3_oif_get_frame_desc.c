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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_frame_desc {int num_entries; int /*<<< orphan*/ * entry; } ;
struct TYPE_2__ {int /*<<< orphan*/ * entry; } ;
struct s5c73m3 {int /*<<< orphan*/  lock; TYPE_1__ frame_desc; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int OIF_SOURCE_PAD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5c73m3_oif_get_frame_desc(struct v4l2_subdev *sd, unsigned int pad,
				  struct v4l2_mbus_frame_desc *fd)
{
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int i;

	if (pad != OIF_SOURCE_PAD || fd == NULL)
		return -EINVAL;

	mutex_lock(&state->lock);
	fd->num_entries = 2;
	for (i = 0; i < fd->num_entries; i++)
		fd->entry[i] = state->frame_desc.entry[i];
	mutex_unlock(&state->lock);

	return 0;
}