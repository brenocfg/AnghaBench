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
struct media_pad {int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct v4l2_subdev *adv748x_get_remote_sd(struct media_pad *pad)
{
	pad = media_entity_remote_pad(pad);
	if (!pad)
		return NULL;

	return media_entity_to_v4l2_subdev(pad->entity);
}