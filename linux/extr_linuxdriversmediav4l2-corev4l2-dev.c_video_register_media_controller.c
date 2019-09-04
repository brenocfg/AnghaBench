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
struct video_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int video_register_media_controller(struct video_device *vdev)
{
#if defined(CONFIG_MEDIA_CONTROLLER)
	u32 intf_type;
	int ret;

	/* Memory-to-memory devices are more complex and use
	 * their own function to register its mc entities.
	 */
	if (!vdev->v4l2_dev->mdev || vdev->vfl_dir == VFL_DIR_M2M)
		return 0;

	vdev->entity.obj_type = MEDIA_ENTITY_TYPE_VIDEO_DEVICE;
	vdev->entity.function = MEDIA_ENT_F_UNKNOWN;

	switch (vdev->vfl_type) {
	case VFL_TYPE_GRABBER:
		intf_type = MEDIA_INTF_T_V4L_VIDEO;
		vdev->entity.function = MEDIA_ENT_F_IO_V4L;
		break;
	case VFL_TYPE_VBI:
		intf_type = MEDIA_INTF_T_V4L_VBI;
		vdev->entity.function = MEDIA_ENT_F_IO_VBI;
		break;
	case VFL_TYPE_SDR:
		intf_type = MEDIA_INTF_T_V4L_SWRADIO;
		vdev->entity.function = MEDIA_ENT_F_IO_SWRADIO;
		break;
	case VFL_TYPE_TOUCH:
		intf_type = MEDIA_INTF_T_V4L_TOUCH;
		vdev->entity.function = MEDIA_ENT_F_IO_V4L;
		break;
	case VFL_TYPE_RADIO:
		intf_type = MEDIA_INTF_T_V4L_RADIO;
		/*
		 * Radio doesn't have an entity at the V4L2 side to represent
		 * radio input or output. Instead, the audio input/output goes
		 * via either physical wires or ALSA.
		 */
		break;
	case VFL_TYPE_SUBDEV:
		intf_type = MEDIA_INTF_T_V4L_SUBDEV;
		/* Entity will be created via v4l2_device_register_subdev() */
		break;
	default:
		return 0;
	}

	if (vdev->entity.function != MEDIA_ENT_F_UNKNOWN) {
		vdev->entity.name = vdev->name;

		/* Needed just for backward compatibility with legacy MC API */
		vdev->entity.info.dev.major = VIDEO_MAJOR;
		vdev->entity.info.dev.minor = vdev->minor;

		ret = media_device_register_entity(vdev->v4l2_dev->mdev,
						   &vdev->entity);
		if (ret < 0) {
			pr_warn("%s: media_device_register_entity failed\n",
				__func__);
			return ret;
		}
	}

	vdev->intf_devnode = media_devnode_create(vdev->v4l2_dev->mdev,
						  intf_type,
						  0, VIDEO_MAJOR,
						  vdev->minor);
	if (!vdev->intf_devnode) {
		media_device_unregister_entity(&vdev->entity);
		return -ENOMEM;
	}

	if (vdev->entity.function != MEDIA_ENT_F_UNKNOWN) {
		struct media_link *link;

		link = media_create_intf_link(&vdev->entity,
					      &vdev->intf_devnode->intf,
					      MEDIA_LNK_FL_ENABLED |
					      MEDIA_LNK_FL_IMMUTABLE);
		if (!link) {
			media_devnode_remove(vdev->intf_devnode);
			media_device_unregister_entity(&vdev->entity);
			return -ENOMEM;
		}
	}

	/* FIXME: how to create the other interface links? */

#endif
	return 0;
}