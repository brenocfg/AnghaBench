#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl_config {char* name; char** qmenu; int type; int /*<<< orphan*/  is_private; int /*<<< orphan*/  elem_size; int /*<<< orphan*/  dims; int /*<<< orphan*/  menu_skip_mask; int /*<<< orphan*/  id; int /*<<< orphan*/  type_ops; int /*<<< orphan*/  ops; int /*<<< orphan*/  def; int /*<<< orphan*/  step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  flags; int /*<<< orphan*/ * qmenu_int; } ;
struct v4l2_ctrl {int /*<<< orphan*/  is_private; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum v4l2_ctrl_type { ____Placeholder_v4l2_ctrl_type } v4l2_ctrl_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int V4L2_CTRL_TYPE_INTEGER_MENU ; 
 int V4L2_CTRL_TYPE_MENU ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_set_err (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_fill (int /*<<< orphan*/ ,char const**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl* v4l2_ctrl_new (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const*,int /*<<< orphan*/  const*,void*) ; 

struct v4l2_ctrl *v4l2_ctrl_new_custom(struct v4l2_ctrl_handler *hdl,
			const struct v4l2_ctrl_config *cfg, void *priv)
{
	bool is_menu;
	struct v4l2_ctrl *ctrl;
	const char *name = cfg->name;
	const char * const *qmenu = cfg->qmenu;
	const s64 *qmenu_int = cfg->qmenu_int;
	enum v4l2_ctrl_type type = cfg->type;
	u32 flags = cfg->flags;
	s64 min = cfg->min;
	s64 max = cfg->max;
	u64 step = cfg->step;
	s64 def = cfg->def;

	if (name == NULL)
		v4l2_ctrl_fill(cfg->id, &name, &type, &min, &max, &step,
								&def, &flags);

	is_menu = (type == V4L2_CTRL_TYPE_MENU ||
		   type == V4L2_CTRL_TYPE_INTEGER_MENU);
	if (is_menu)
		WARN_ON(step);
	else
		WARN_ON(cfg->menu_skip_mask);
	if (type == V4L2_CTRL_TYPE_MENU && !qmenu) {
		qmenu = v4l2_ctrl_get_menu(cfg->id);
	} else if (type == V4L2_CTRL_TYPE_INTEGER_MENU && !qmenu_int) {
		handler_set_err(hdl, -EINVAL);
		return NULL;
	}

	ctrl = v4l2_ctrl_new(hdl, cfg->ops, cfg->type_ops, cfg->id, name,
			type, min, max,
			is_menu ? cfg->menu_skip_mask : step, def,
			cfg->dims, cfg->elem_size,
			flags, qmenu, qmenu_int, priv);
	if (ctrl)
		ctrl->is_private = cfg->is_private;
	return ctrl;
}