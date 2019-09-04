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
struct v4l2_mbus_frame_desc {int num_entries; TYPE_1__* entry; } ;
struct s5c73m3 {int /*<<< orphan*/  lock; struct v4l2_mbus_frame_desc frame_desc; } ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int OIF_SOURCE_PAD ; 
 int /*<<< orphan*/  S5C73M3_EMBEDDED_DATA_MAXLEN ; 
 int SZ_1M ; 
 int max_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int s5c73m3_oif_set_frame_desc(struct v4l2_subdev *sd, unsigned int pad,
				      struct v4l2_mbus_frame_desc *fd)
{
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	struct v4l2_mbus_frame_desc *frame_desc = &state->frame_desc;
	int i;

	if (pad != OIF_SOURCE_PAD || fd == NULL)
		return -EINVAL;

	fd->entry[0].length = 10 * SZ_1M;
	fd->entry[1].length = max_t(u32, fd->entry[1].length,
				    S5C73M3_EMBEDDED_DATA_MAXLEN);
	fd->num_entries = 2;

	mutex_lock(&state->lock);
	for (i = 0; i < fd->num_entries; i++)
		frame_desc->entry[i] = fd->entry[i];
	mutex_unlock(&state->lock);

	return 0;
}