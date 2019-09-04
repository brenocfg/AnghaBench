#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vsp1_device {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_7__ {TYPE_4__* ctrl_handler; } ;
struct TYPE_8__ {TYPE_1__ subdev; int /*<<< orphan*/  vsp1; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct vsp1_clu {TYPE_4__ ctrls; TYPE_2__ entity; int /*<<< orphan*/  pool; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ CLU_SIZE ; 
 int ENOMEM ; 
 struct vsp1_clu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_LUT ; 
 int /*<<< orphan*/  VSP1_ENTITY_CLU ; 
 int /*<<< orphan*/  clu_entity_ops ; 
 int /*<<< orphan*/  clu_mode_control ; 
 int /*<<< orphan*/  clu_ops ; 
 int /*<<< orphan*/  clu_table_control ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct vsp1_clu* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_dl_body_pool_create (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_entity_destroy (TYPE_2__*) ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_2__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct vsp1_clu *vsp1_clu_create(struct vsp1_device *vsp1)
{
	struct vsp1_clu *clu;
	int ret;

	clu = devm_kzalloc(vsp1->dev, sizeof(*clu), GFP_KERNEL);
	if (clu == NULL)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&clu->lock);

	clu->entity.ops = &clu_entity_ops;
	clu->entity.type = VSP1_ENTITY_CLU;

	ret = vsp1_entity_init(vsp1, &clu->entity, "clu", 2, &clu_ops,
			       MEDIA_ENT_F_PROC_VIDEO_LUT);
	if (ret < 0)
		return ERR_PTR(ret);

	/*
	 * Pre-allocate a body pool, with 3 bodies allowing a userspace update
	 * before the hardware has committed a previous set of tables, handling
	 * both the queued and pending dl entries. One extra entry is added to
	 * the CLU_SIZE to allow for the VI6_CLU_ADDR header.
	 */
	clu->pool = vsp1_dl_body_pool_create(clu->entity.vsp1, 3, CLU_SIZE + 1,
					     0);
	if (!clu->pool)
		return ERR_PTR(-ENOMEM);

	/* Initialize the control handler. */
	v4l2_ctrl_handler_init(&clu->ctrls, 2);
	v4l2_ctrl_new_custom(&clu->ctrls, &clu_table_control, NULL);
	v4l2_ctrl_new_custom(&clu->ctrls, &clu_mode_control, NULL);

	clu->entity.subdev.ctrl_handler = &clu->ctrls;

	if (clu->ctrls.error) {
		dev_err(vsp1->dev, "clu: failed to initialize controls\n");
		ret = clu->ctrls.error;
		vsp1_entity_destroy(&clu->entity);
		return ERR_PTR(ret);
	}

	v4l2_ctrl_handler_setup(&clu->ctrls);

	return clu;
}