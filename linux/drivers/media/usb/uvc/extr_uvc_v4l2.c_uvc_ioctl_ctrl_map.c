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
struct uvc_xu_control_mapping {int v4l2_type; int menu_count; int /*<<< orphan*/  menu_info; int /*<<< orphan*/  data_type; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  selector; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct uvc_video_chain {int dummy; } ;
struct uvc_control_mapping {int v4l2_type; int menu_count; struct uvc_control_mapping* menu_info; int /*<<< orphan*/  data_type; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  selector; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct uvc_control_mapping*) ; 
 int PTR_ERR (struct uvc_control_mapping*) ; 
 int UVC_MAX_CONTROL_MENU_ENTRIES ; 
 int /*<<< orphan*/  UVC_TRACE_CONTROL ; 
#define  V4L2_CTRL_TYPE_BOOLEAN 131 
#define  V4L2_CTRL_TYPE_BUTTON 130 
#define  V4L2_CTRL_TYPE_INTEGER 129 
#define  V4L2_CTRL_TYPE_MENU 128 
 int /*<<< orphan*/  kfree (struct uvc_control_mapping*) ; 
 struct uvc_control_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct uvc_control_mapping* memdup_user (int /*<<< orphan*/ ,unsigned int) ; 
 int uvc_ctrl_add_mapping (struct uvc_video_chain*,struct uvc_control_mapping*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int uvc_ioctl_ctrl_map(struct uvc_video_chain *chain,
	struct uvc_xu_control_mapping *xmap)
{
	struct uvc_control_mapping *map;
	unsigned int size;
	int ret;

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (map == NULL)
		return -ENOMEM;

	map->id = xmap->id;
	memcpy(map->name, xmap->name, sizeof(map->name));
	memcpy(map->entity, xmap->entity, sizeof(map->entity));
	map->selector = xmap->selector;
	map->size = xmap->size;
	map->offset = xmap->offset;
	map->v4l2_type = xmap->v4l2_type;
	map->data_type = xmap->data_type;

	switch (xmap->v4l2_type) {
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_BUTTON:
		break;

	case V4L2_CTRL_TYPE_MENU:
		/* Prevent excessive memory consumption, as well as integer
		 * overflows.
		 */
		if (xmap->menu_count == 0 ||
		    xmap->menu_count > UVC_MAX_CONTROL_MENU_ENTRIES) {
			ret = -EINVAL;
			goto free_map;
		}

		size = xmap->menu_count * sizeof(*map->menu_info);
		map->menu_info = memdup_user(xmap->menu_info, size);
		if (IS_ERR(map->menu_info)) {
			ret = PTR_ERR(map->menu_info);
			goto free_map;
		}

		map->menu_count = xmap->menu_count;
		break;

	default:
		uvc_trace(UVC_TRACE_CONTROL, "Unsupported V4L2 control type "
			  "%u.\n", xmap->v4l2_type);
		ret = -ENOTTY;
		goto free_map;
	}

	ret = uvc_ctrl_add_mapping(chain, map);

	kfree(map->menu_info);
free_map:
	kfree(map);

	return ret;
}