#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_config {scalar_t__ id; int /*<<< orphan*/  flags; int /*<<< orphan*/  def; int /*<<< orphan*/  step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  menu_skip_mask; } ;
struct v4l2_flash_ctrl_data {scalar_t__ cid; struct v4l2_ctrl_config config; } ;
struct v4l2_flash_config {int dummy; } ;
struct TYPE_8__ {int error; } ;
struct TYPE_7__ {TYPE_2__* ctrl_handler; int /*<<< orphan*/  dev; } ;
struct v4l2_flash {TYPE_2__ hdl; TYPE_1__ sd; struct v4l2_ctrl** ctrls; } ;
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_FLASH_CTRLS ; 
 int STROBE_SOURCE ; 
 scalar_t__ V4L2_CID_FLASH_LED_MODE ; 
 scalar_t__ V4L2_CID_FLASH_STROBE_SOURCE ; 
 int /*<<< orphan*/  __fill_ctrl_init_data (struct v4l2_flash*,struct v4l2_flash_config*,struct v4l2_flash_ctrl_data*) ; 
 struct v4l2_ctrl** devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct v4l2_flash_ctrl_data* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v4l2_flash_ctrl_data*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std_menu (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_flash_ctrl_ops ; 

__attribute__((used)) static int v4l2_flash_init_controls(struct v4l2_flash *v4l2_flash,
				struct v4l2_flash_config *flash_cfg)

{
	struct v4l2_flash_ctrl_data *ctrl_init_data;
	struct v4l2_ctrl *ctrl;
	struct v4l2_ctrl_config *ctrl_cfg;
	int i, ret, num_ctrls = 0;

	v4l2_flash->ctrls = devm_kcalloc(v4l2_flash->sd.dev,
					STROBE_SOURCE + 1,
					sizeof(*v4l2_flash->ctrls),
					GFP_KERNEL);
	if (!v4l2_flash->ctrls)
		return -ENOMEM;

	/* allocate memory dynamically so as not to exceed stack frame size */
	ctrl_init_data = kcalloc(NUM_FLASH_CTRLS, sizeof(*ctrl_init_data),
					GFP_KERNEL);
	if (!ctrl_init_data)
		return -ENOMEM;

	__fill_ctrl_init_data(v4l2_flash, flash_cfg, ctrl_init_data);

	for (i = 0; i < NUM_FLASH_CTRLS; ++i)
		if (ctrl_init_data[i].cid)
			++num_ctrls;

	v4l2_ctrl_handler_init(&v4l2_flash->hdl, num_ctrls);

	for (i = 0; i < NUM_FLASH_CTRLS; ++i) {
		ctrl_cfg = &ctrl_init_data[i].config;
		if (!ctrl_init_data[i].cid)
			continue;

		if (ctrl_cfg->id == V4L2_CID_FLASH_LED_MODE ||
		    ctrl_cfg->id == V4L2_CID_FLASH_STROBE_SOURCE)
			ctrl = v4l2_ctrl_new_std_menu(&v4l2_flash->hdl,
						&v4l2_flash_ctrl_ops,
						ctrl_cfg->id,
						ctrl_cfg->max,
						ctrl_cfg->menu_skip_mask,
						ctrl_cfg->def);
		else
			ctrl = v4l2_ctrl_new_std(&v4l2_flash->hdl,
						&v4l2_flash_ctrl_ops,
						ctrl_cfg->id,
						ctrl_cfg->min,
						ctrl_cfg->max,
						ctrl_cfg->step,
						ctrl_cfg->def);

		if (ctrl)
			ctrl->flags |= ctrl_cfg->flags;

		if (i <= STROBE_SOURCE)
			v4l2_flash->ctrls[i] = ctrl;
	}

	kfree(ctrl_init_data);

	if (v4l2_flash->hdl.error) {
		ret = v4l2_flash->hdl.error;
		goto error_free_handler;
	}

	v4l2_ctrl_handler_setup(&v4l2_flash->hdl);

	v4l2_flash->sd.ctrl_handler = &v4l2_flash->hdl;

	return 0;

error_free_handler:
	v4l2_ctrl_handler_free(&v4l2_flash->hdl);
	return ret;
}