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
struct vsp1_uif {int m3w_quirk; TYPE_1__ entity; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_uif* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_STATISTICS ; 
 int /*<<< orphan*/  VSP1_ENTITY_UIF ; 
 struct vsp1_uif* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  uif_entity_ops ; 
 int /*<<< orphan*/  uif_ops ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_r8a7796 ; 

struct vsp1_uif *vsp1_uif_create(struct vsp1_device *vsp1, unsigned int index)
{
	struct vsp1_uif *uif;
	char name[6];
	int ret;

	uif = devm_kzalloc(vsp1->dev, sizeof(*uif), GFP_KERNEL);
	if (!uif)
		return ERR_PTR(-ENOMEM);

	if (soc_device_match(vsp1_r8a7796))
		uif->m3w_quirk = true;

	uif->entity.ops = &uif_entity_ops;
	uif->entity.type = VSP1_ENTITY_UIF;
	uif->entity.index = index;

	/* The datasheet names the two UIF instances UIF4 and UIF5. */
	sprintf(name, "uif.%u", index + 4);
	ret = vsp1_entity_init(vsp1, &uif->entity, name, 2, &uif_ops,
			       MEDIA_ENT_F_PROC_VIDEO_STATISTICS);
	if (ret < 0)
		return ERR_PTR(ret);

	return uif;
}