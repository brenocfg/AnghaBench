#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int index; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct vsp1_rwpf {TYPE_1__ entity; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_rwpf* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER ; 
 int /*<<< orphan*/  RPF_MAX_HEIGHT ; 
 int /*<<< orphan*/  RPF_MAX_WIDTH ; 
 int /*<<< orphan*/  VSP1_ENTITY_RPF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct vsp1_rwpf* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpf_entity_ops ; 
 int /*<<< orphan*/  rpf_ops ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_entity_destroy (TYPE_1__*) ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vsp1_rwpf_init_ctrls (struct vsp1_rwpf*,int /*<<< orphan*/ ) ; 

struct vsp1_rwpf *vsp1_rpf_create(struct vsp1_device *vsp1, unsigned int index)
{
	struct vsp1_rwpf *rpf;
	char name[6];
	int ret;

	rpf = devm_kzalloc(vsp1->dev, sizeof(*rpf), GFP_KERNEL);
	if (rpf == NULL)
		return ERR_PTR(-ENOMEM);

	rpf->max_width = RPF_MAX_WIDTH;
	rpf->max_height = RPF_MAX_HEIGHT;

	rpf->entity.ops = &rpf_entity_ops;
	rpf->entity.type = VSP1_ENTITY_RPF;
	rpf->entity.index = index;

	sprintf(name, "rpf.%u", index);
	ret = vsp1_entity_init(vsp1, &rpf->entity, name, 2, &rpf_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	if (ret < 0)
		return ERR_PTR(ret);

	/* Initialize the control handler. */
	ret = vsp1_rwpf_init_ctrls(rpf, 0);
	if (ret < 0) {
		dev_err(vsp1->dev, "rpf%u: failed to initialize controls\n",
			index);
		goto error;
	}

	v4l2_ctrl_handler_setup(&rpf->ctrls);

	return rpf;

error:
	vsp1_entity_destroy(&rpf->entity);
	return ERR_PTR(ret);
}