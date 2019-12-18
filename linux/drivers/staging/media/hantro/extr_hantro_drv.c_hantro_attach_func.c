#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct media_link {int dummy; } ;
struct media_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  entity; int /*<<< orphan*/  minor; } ;
struct TYPE_6__ {void* flags; } ;
struct hantro_func {TYPE_4__ vdev; int /*<<< orphan*/  proc; int /*<<< orphan*/  sink; TYPE_1__* intf_devnode; TYPE_3__ sink_pad; int /*<<< orphan*/  id; TYPE_3__* proc_pads; TYPE_3__ source_pad; } ;
struct hantro_dev {struct media_device mdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MEDIA_ENT_F_IO_V4L ; 
 int /*<<< orphan*/  MEDIA_INTF_T_V4L_VIDEO ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_LNK_FL_IMMUTABLE ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  VIDEO_MAJOR ; 
 int hantro_register_entity (struct media_device*,int /*<<< orphan*/ *,char*,TYPE_3__*,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 struct media_link* media_create_intf_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  media_device_unregister_entity (int /*<<< orphan*/ *) ; 
 TYPE_1__* media_devnode_create (struct media_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_devnode_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  media_entity_remove_links (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hantro_attach_func(struct hantro_dev *vpu,
			      struct hantro_func *func)
{
	struct media_device *mdev = &vpu->mdev;
	struct media_link *link;
	int ret;

	/* Create the three encoder entities with their pads */
	func->source_pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = hantro_register_entity(mdev, &func->vdev.entity, "source",
				     &func->source_pad, 1, MEDIA_ENT_F_IO_V4L,
				     &func->vdev);
	if (ret)
		return ret;

	func->proc_pads[0].flags = MEDIA_PAD_FL_SINK;
	func->proc_pads[1].flags = MEDIA_PAD_FL_SOURCE;
	ret = hantro_register_entity(mdev, &func->proc, "proc",
				     func->proc_pads, 2, func->id,
				     &func->vdev);
	if (ret)
		goto err_rel_entity0;

	func->sink_pad.flags = MEDIA_PAD_FL_SINK;
	ret = hantro_register_entity(mdev, &func->sink, "sink",
				     &func->sink_pad, 1, MEDIA_ENT_F_IO_V4L,
				     &func->vdev);
	if (ret)
		goto err_rel_entity1;

	/* Connect the three entities */
	ret = media_create_pad_link(&func->vdev.entity, 0, &func->proc, 1,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	if (ret)
		goto err_rel_entity2;

	ret = media_create_pad_link(&func->proc, 0, &func->sink, 0,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	if (ret)
		goto err_rm_links0;

	/* Create video interface */
	func->intf_devnode = media_devnode_create(mdev, MEDIA_INTF_T_V4L_VIDEO,
						  0, VIDEO_MAJOR,
						  func->vdev.minor);
	if (!func->intf_devnode) {
		ret = -ENOMEM;
		goto err_rm_links1;
	}

	/* Connect the two DMA engines to the interface */
	link = media_create_intf_link(&func->vdev.entity,
				      &func->intf_devnode->intf,
				      MEDIA_LNK_FL_IMMUTABLE |
				      MEDIA_LNK_FL_ENABLED);
	if (!link) {
		ret = -ENOMEM;
		goto err_rm_devnode;
	}

	link = media_create_intf_link(&func->sink, &func->intf_devnode->intf,
				      MEDIA_LNK_FL_IMMUTABLE |
				      MEDIA_LNK_FL_ENABLED);
	if (!link) {
		ret = -ENOMEM;
		goto err_rm_devnode;
	}
	return 0;

err_rm_devnode:
	media_devnode_remove(func->intf_devnode);

err_rm_links1:
	media_entity_remove_links(&func->sink);

err_rm_links0:
	media_entity_remove_links(&func->proc);
	media_entity_remove_links(&func->vdev.entity);

err_rel_entity2:
	media_device_unregister_entity(&func->sink);

err_rel_entity1:
	media_device_unregister_entity(&func->proc);

err_rel_entity0:
	media_device_unregister_entity(&func->vdev.entity);
	return ret;
}