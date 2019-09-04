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
struct vsp1_uds {TYPE_1__ entity; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_uds* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_SCALER ; 
 int /*<<< orphan*/  VSP1_ENTITY_UDS ; 
 struct vsp1_uds* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  uds_entity_ops ; 
 int /*<<< orphan*/  uds_ops ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct vsp1_uds *vsp1_uds_create(struct vsp1_device *vsp1, unsigned int index)
{
	struct vsp1_uds *uds;
	char name[6];
	int ret;

	uds = devm_kzalloc(vsp1->dev, sizeof(*uds), GFP_KERNEL);
	if (uds == NULL)
		return ERR_PTR(-ENOMEM);

	uds->entity.ops = &uds_entity_ops;
	uds->entity.type = VSP1_ENTITY_UDS;
	uds->entity.index = index;

	sprintf(name, "uds.%u", index);
	ret = vsp1_entity_init(vsp1, &uds->entity, name, 2, &uds_ops,
			       MEDIA_ENT_F_PROC_VIDEO_SCALER);
	if (ret < 0)
		return ERR_PTR(ret);

	return uds;
}