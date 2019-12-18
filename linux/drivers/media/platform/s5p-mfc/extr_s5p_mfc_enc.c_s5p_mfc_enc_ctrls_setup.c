#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_config {scalar_t__ type; scalar_t__ menu_skip_mask; scalar_t__ step; int /*<<< orphan*/  id; int /*<<< orphan*/  qmenu; scalar_t__ flags; int /*<<< orphan*/  name; int /*<<< orphan*/  def; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/ * ops; } ;
struct TYPE_11__ {int error; } ;
struct s5p_mfc_ctx {TYPE_2__ ctrl_handler; TYPE_1__** ctrls; } ;
struct TYPE_12__ {scalar_t__ type; scalar_t__ is_volatile; int /*<<< orphan*/  default_value; scalar_t__ step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  id; scalar_t__ menu_skip_mask; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ IS_MFC51_PRIV (int /*<<< orphan*/ ) ; 
 int NUM_CTRLS ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_VOLATILE ; 
 scalar_t__ V4L2_CTRL_TYPE_INTEGER_MENU ; 
 scalar_t__ V4L2_CTRL_TYPE_MENU ; 
 TYPE_9__* controls ; 
 int /*<<< orphan*/  memset (struct v4l2_ctrl_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfc51_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*,...) ; 
 int /*<<< orphan*/  s5p_mfc_enc_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 TYPE_1__* v4l2_ctrl_new_custom (TYPE_2__*,struct v4l2_ctrl_config*,int /*<<< orphan*/ *) ; 
 TYPE_1__* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* v4l2_ctrl_new_std_menu (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int s5p_mfc_enc_ctrls_setup(struct s5p_mfc_ctx *ctx)
{
	struct v4l2_ctrl_config cfg;
	int i;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, NUM_CTRLS);
	if (ctx->ctrl_handler.error) {
		mfc_err("v4l2_ctrl_handler_init failed\n");
		return ctx->ctrl_handler.error;
	}
	for (i = 0; i < NUM_CTRLS; i++) {
		if (IS_MFC51_PRIV(controls[i].id)) {
			memset(&cfg, 0, sizeof(struct v4l2_ctrl_config));
			cfg.ops = &s5p_mfc_enc_ctrl_ops;
			cfg.id = controls[i].id;
			cfg.min = controls[i].minimum;
			cfg.max = controls[i].maximum;
			cfg.def = controls[i].default_value;
			cfg.name = controls[i].name;
			cfg.type = controls[i].type;
			cfg.flags = 0;

			if (cfg.type == V4L2_CTRL_TYPE_MENU) {
				cfg.step = 0;
				cfg.menu_skip_mask = controls[i].menu_skip_mask;
				cfg.qmenu = mfc51_get_menu(cfg.id);
			} else {
				cfg.step = controls[i].step;
				cfg.menu_skip_mask = 0;
			}
			ctx->ctrls[i] = v4l2_ctrl_new_custom(&ctx->ctrl_handler,
					&cfg, NULL);
		} else {
			if ((controls[i].type == V4L2_CTRL_TYPE_MENU) ||
				(controls[i].type ==
					V4L2_CTRL_TYPE_INTEGER_MENU)) {
				ctx->ctrls[i] = v4l2_ctrl_new_std_menu(
					&ctx->ctrl_handler,
					&s5p_mfc_enc_ctrl_ops, controls[i].id,
					controls[i].maximum, 0,
					controls[i].default_value);
			} else {
				ctx->ctrls[i] = v4l2_ctrl_new_std(
					&ctx->ctrl_handler,
					&s5p_mfc_enc_ctrl_ops, controls[i].id,
					controls[i].minimum,
					controls[i].maximum, controls[i].step,
					controls[i].default_value);
			}
		}
		if (ctx->ctrl_handler.error) {
			mfc_err("Adding control (%d) failed\n", i);
			return ctx->ctrl_handler.error;
		}
		if (controls[i].is_volatile && ctx->ctrls[i])
			ctx->ctrls[i]->flags |= V4L2_CTRL_FLAG_VOLATILE;
	}
	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	return 0;
}