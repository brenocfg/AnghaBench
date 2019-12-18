#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vsp1_device {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_8__ {TYPE_5__* ctrl_handler; } ;
struct TYPE_9__ {int type; TYPE_2__ subdev; int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {int error; } ;
struct vsp1_brx {TYPE_3__ entity; TYPE_5__ ctrls; scalar_t__ bgcolor; int /*<<< orphan*/  base; } ;
typedef  enum vsp1_entity_type { ____Placeholder_vsp1_entity_type } vsp1_entity_type ;
struct TYPE_7__ {int num_bru_inputs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_brx* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_COMPOSER ; 
 int /*<<< orphan*/  V4L2_CID_BG_COLOR ; 
 int /*<<< orphan*/  VI6_BRS_BASE ; 
 int /*<<< orphan*/  VI6_BRU_BASE ; 
 int VSP1_ENTITY_BRU ; 
 int /*<<< orphan*/  brx_ctrl_ops ; 
 int /*<<< orphan*/  brx_entity_ops ; 
 int /*<<< orphan*/  brx_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 struct vsp1_brx* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_5__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_entity_destroy (TYPE_3__*) ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_3__*,char const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct vsp1_brx *vsp1_brx_create(struct vsp1_device *vsp1,
				 enum vsp1_entity_type type)
{
	struct vsp1_brx *brx;
	unsigned int num_pads;
	const char *name;
	int ret;

	brx = devm_kzalloc(vsp1->dev, sizeof(*brx), GFP_KERNEL);
	if (brx == NULL)
		return ERR_PTR(-ENOMEM);

	brx->base = type == VSP1_ENTITY_BRU ? VI6_BRU_BASE : VI6_BRS_BASE;
	brx->entity.ops = &brx_entity_ops;
	brx->entity.type = type;

	if (type == VSP1_ENTITY_BRU) {
		num_pads = vsp1->info->num_bru_inputs + 1;
		name = "bru";
	} else {
		num_pads = 3;
		name = "brs";
	}

	ret = vsp1_entity_init(vsp1, &brx->entity, name, num_pads, &brx_ops,
			       MEDIA_ENT_F_PROC_VIDEO_COMPOSER);
	if (ret < 0)
		return ERR_PTR(ret);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&brx->ctrls, 1);
	v4l2_ctrl_new_std(&brx->ctrls, &brx_ctrl_ops, V4L2_CID_BG_COLOR,
			  0, 0xffffff, 1, 0);

	brx->bgcolor = 0;

	brx->entity.subdev.ctrl_handler = &brx->ctrls;

	if (brx->ctrls.error) {
		dev_err(vsp1->dev, "%s: failed to initialize controls\n", name);
		ret = brx->ctrls.error;
		vsp1_entity_destroy(&brx->entity);
		return ERR_PTR(ret);
	}

	return brx;
}