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
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct media_pad {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct media_entity {char* name; int function; TYPE_2__ info; int /*<<< orphan*/  obj_type; } ;
struct media_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENTITY_TYPE_BASE ; 
 int MEDIA_ENT_F_IO_V4L ; 
 int /*<<< orphan*/  VIDEO_MAJOR ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int media_device_register_entity (struct media_device*,struct media_entity*) ; 
 int media_entity_pads_init (struct media_entity*,int,struct media_pad*) ; 

__attribute__((used)) static int hantro_register_entity(struct media_device *mdev,
				  struct media_entity *entity,
				  const char *entity_name,
				  struct media_pad *pads, int num_pads,
				  int function, struct video_device *vdev)
{
	char *name;
	int ret;

	entity->obj_type = MEDIA_ENTITY_TYPE_BASE;
	if (function == MEDIA_ENT_F_IO_V4L) {
		entity->info.dev.major = VIDEO_MAJOR;
		entity->info.dev.minor = vdev->minor;
	}

	name = devm_kasprintf(mdev->dev, GFP_KERNEL, "%s-%s", vdev->name,
			      entity_name);
	if (!name)
		return -ENOMEM;

	entity->name = name;
	entity->function = function;

	ret = media_entity_pads_init(entity, num_pads, pads);
	if (ret)
		return ret;

	ret = media_device_register_entity(mdev, entity);
	if (ret)
		return ret;

	return 0;
}