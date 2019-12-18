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
struct TYPE_2__ {unsigned int index; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct vsp1_lif {TYPE_1__ entity; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_lif* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER ; 
 int /*<<< orphan*/  VSP1_ENTITY_LIF ; 
 struct vsp1_lif* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lif_entity_ops ; 
 int /*<<< orphan*/  lif_ops ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct vsp1_lif *vsp1_lif_create(struct vsp1_device *vsp1, unsigned int index)
{
	struct vsp1_lif *lif;
	int ret;

	lif = devm_kzalloc(vsp1->dev, sizeof(*lif), GFP_KERNEL);
	if (lif == NULL)
		return ERR_PTR(-ENOMEM);

	lif->entity.ops = &lif_entity_ops;
	lif->entity.type = VSP1_ENTITY_LIF;
	lif->entity.index = index;

	/*
	 * The LIF is never exposed to userspace, but media entity registration
	 * requires a function to be set. Use PROC_VIDEO_PIXEL_FORMATTER just to
	 * avoid triggering a WARN_ON(), the value won't be seen anywhere.
	 */
	ret = vsp1_entity_init(vsp1, &lif->entity, "lif", 2, &lif_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	if (ret < 0)
		return ERR_PTR(ret);

	return lif;
}