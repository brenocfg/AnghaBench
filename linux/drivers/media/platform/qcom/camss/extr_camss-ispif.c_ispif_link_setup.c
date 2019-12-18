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
struct media_pad {int flags; int /*<<< orphan*/  entity; } ;
struct media_entity {int dummy; } ;
struct ispif_line {int /*<<< orphan*/  interface; int /*<<< orphan*/  vfe_id; int /*<<< orphan*/  csid_id; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;

/* Variables and functions */
 int EBUSY ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  ispif_get_intf (int) ; 
 scalar_t__ media_entity_remote_pad (struct media_pad const*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  msm_csid_get_csid_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_vfe_get_vfe_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_vfe_get_vfe_line_id (int /*<<< orphan*/ ,int*) ; 
 struct ispif_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ispif_link_setup(struct media_entity *entity,
			    const struct media_pad *local,
			    const struct media_pad *remote, u32 flags)
{
	if (flags & MEDIA_LNK_FL_ENABLED) {
		if (media_entity_remote_pad(local))
			return -EBUSY;

		if (local->flags & MEDIA_PAD_FL_SINK) {
			struct v4l2_subdev *sd;
			struct ispif_line *line;

			sd = media_entity_to_v4l2_subdev(entity);
			line = v4l2_get_subdevdata(sd);

			msm_csid_get_csid_id(remote->entity, &line->csid_id);
		} else { /* MEDIA_PAD_FL_SOURCE */
			struct v4l2_subdev *sd;
			struct ispif_line *line;
			enum vfe_line_id id;

			sd = media_entity_to_v4l2_subdev(entity);
			line = v4l2_get_subdevdata(sd);

			msm_vfe_get_vfe_id(remote->entity, &line->vfe_id);
			msm_vfe_get_vfe_line_id(remote->entity, &id);
			line->interface = ispif_get_intf(id);
		}
	}

	return 0;
}