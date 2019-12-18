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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {int /*<<< orphan*/  name; } ;
struct csi_state {int sink_linked; int /*<<< orphan*/  lock; struct v4l2_subdev* src_sd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipi_csis_link_setup(struct media_entity *entity,
				const struct media_pad *local_pad,
				const struct media_pad *remote_pad, u32 flags)
{
	struct v4l2_subdev *mipi_sd = media_entity_to_v4l2_subdev(entity);
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	struct v4l2_subdev *remote_sd;
	int ret = 0;

	dev_dbg(state->dev, "link setup %s -> %s", remote_pad->entity->name,
		local_pad->entity->name);

	remote_sd = media_entity_to_v4l2_subdev(remote_pad->entity);

	mutex_lock(&state->lock);

	if (local_pad->flags & MEDIA_PAD_FL_SOURCE) {
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (state->sink_linked) {
				ret = -EBUSY;
				goto out;
			}
			state->sink_linked = true;
		} else {
			state->sink_linked = false;
		}
	} else {
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (state->src_sd) {
				ret = -EBUSY;
				goto out;
			}
			state->src_sd = remote_sd;
		} else {
			state->src_sd = NULL;
		}
	}

out:
	mutex_unlock(&state->lock);
	return ret;
}