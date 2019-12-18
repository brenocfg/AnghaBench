#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int index; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct vsp1_rwpf {TYPE_2__ entity; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  dlm; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct vsp1_device {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_rwpf* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER ; 
 int /*<<< orphan*/  VSP1_ENTITY_WPF ; 
 int /*<<< orphan*/  WPF_GEN2_MAX_HEIGHT ; 
 int /*<<< orphan*/  WPF_GEN2_MAX_WIDTH ; 
 int /*<<< orphan*/  WPF_GEN3_MAX_HEIGHT ; 
 int /*<<< orphan*/  WPF_GEN3_MAX_WIDTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct vsp1_rwpf* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_dlm_create (struct vsp1_device*,unsigned int,int) ; 
 int /*<<< orphan*/  vsp1_entity_destroy (TYPE_2__*) ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_2__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpf_entity_ops ; 
 int wpf_init_controls (struct vsp1_rwpf*) ; 
 int /*<<< orphan*/  wpf_ops ; 

struct vsp1_rwpf *vsp1_wpf_create(struct vsp1_device *vsp1, unsigned int index)
{
	struct vsp1_rwpf *wpf;
	char name[6];
	int ret;

	wpf = devm_kzalloc(vsp1->dev, sizeof(*wpf), GFP_KERNEL);
	if (wpf == NULL)
		return ERR_PTR(-ENOMEM);

	if (vsp1->info->gen == 2) {
		wpf->max_width = WPF_GEN2_MAX_WIDTH;
		wpf->max_height = WPF_GEN2_MAX_HEIGHT;
	} else {
		wpf->max_width = WPF_GEN3_MAX_WIDTH;
		wpf->max_height = WPF_GEN3_MAX_HEIGHT;
	}

	wpf->entity.ops = &wpf_entity_ops;
	wpf->entity.type = VSP1_ENTITY_WPF;
	wpf->entity.index = index;

	sprintf(name, "wpf.%u", index);
	ret = vsp1_entity_init(vsp1, &wpf->entity, name, 2, &wpf_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	if (ret < 0)
		return ERR_PTR(ret);

	/* Initialize the display list manager. */
	wpf->dlm = vsp1_dlm_create(vsp1, index, 64);
	if (!wpf->dlm) {
		ret = -ENOMEM;
		goto error;
	}

	/* Initialize the control handler. */
	ret = wpf_init_controls(wpf);
	if (ret < 0) {
		dev_err(vsp1->dev, "wpf%u: failed to initialize controls\n",
			index);
		goto error;
	}

	v4l2_ctrl_handler_setup(&wpf->ctrls);

	return wpf;

error:
	vsp1_entity_destroy(&wpf->entity);
	return ERR_PTR(ret);
}