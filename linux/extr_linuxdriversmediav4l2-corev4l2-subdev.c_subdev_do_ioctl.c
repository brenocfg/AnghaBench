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
struct video_device {int dummy; } ;
struct v4l2_subdev {int flags; int /*<<< orphan*/  name; } ;
struct v4l2_fh {int /*<<< orphan*/  ctrl_handler; } ;
struct file {int f_flags; struct v4l2_fh* private_data; } ;

/* Variables and functions */
 long ENOIOCTLCMD ; 
 long ENOTTY ; 
 int O_NONBLOCK ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
#define  VIDIOC_DQEVENT 139 
#define  VIDIOC_G_CTRL 138 
#define  VIDIOC_G_EXT_CTRLS 137 
#define  VIDIOC_LOG_STATUS 136 
#define  VIDIOC_QUERYCTRL 135 
#define  VIDIOC_QUERYMENU 134 
#define  VIDIOC_QUERY_EXT_CTRL 133 
#define  VIDIOC_SUBSCRIBE_EVENT 132 
#define  VIDIOC_S_CTRL 131 
#define  VIDIOC_S_EXT_CTRLS 130 
#define  VIDIOC_TRY_EXT_CTRLS 129 
#define  VIDIOC_UNSUBSCRIBE_EVENT 128 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscribe_event ; 
 int /*<<< orphan*/  unsubscribe_event ; 
 long v4l2_event_dequeue (struct v4l2_fh*,void*,int) ; 
 long v4l2_g_ctrl (int /*<<< orphan*/ ,void*) ; 
 long v4l2_g_ext_ctrls (int /*<<< orphan*/ ,void*) ; 
 long v4l2_query_ext_ctrl (int /*<<< orphan*/ ,void*) ; 
 long v4l2_queryctrl (int /*<<< orphan*/ ,void*) ; 
 long v4l2_querymenu (int /*<<< orphan*/ ,void*) ; 
 long v4l2_s_ctrl (struct v4l2_fh*,int /*<<< orphan*/ ,void*) ; 
 long v4l2_s_ext_ctrls (struct v4l2_fh*,int /*<<< orphan*/ ,void*) ; 
 long v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 long v4l2_try_ext_ctrls (int /*<<< orphan*/ ,void*) ; 
 struct v4l2_subdev* vdev_to_v4l2_subdev (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static long subdev_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	struct video_device *vdev = video_devdata(file);
	struct v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	struct v4l2_fh *vfh = file->private_data;
#if defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	struct v4l2_subdev_fh *subdev_fh = to_v4l2_subdev_fh(vfh);
	int rval;
#endif

	switch (cmd) {
	case VIDIOC_QUERYCTRL:
		/*
		 * TODO: this really should be folded into v4l2_queryctrl (this
		 * currently returns -EINVAL for NULL control handlers).
		 * However, v4l2_queryctrl() is still called directly by
		 * drivers as well and until that has been addressed I believe
		 * it is safer to do the check here. The same is true for the
		 * other control ioctls below.
		 */
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_queryctrl(vfh->ctrl_handler, arg);

	case VIDIOC_QUERY_EXT_CTRL:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_query_ext_ctrl(vfh->ctrl_handler, arg);

	case VIDIOC_QUERYMENU:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_querymenu(vfh->ctrl_handler, arg);

	case VIDIOC_G_CTRL:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_g_ctrl(vfh->ctrl_handler, arg);

	case VIDIOC_S_CTRL:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_s_ctrl(vfh, vfh->ctrl_handler, arg);

	case VIDIOC_G_EXT_CTRLS:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_g_ext_ctrls(vfh->ctrl_handler, arg);

	case VIDIOC_S_EXT_CTRLS:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_s_ext_ctrls(vfh, vfh->ctrl_handler, arg);

	case VIDIOC_TRY_EXT_CTRLS:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_try_ext_ctrls(vfh->ctrl_handler, arg);

	case VIDIOC_DQEVENT:
		if (!(sd->flags & V4L2_SUBDEV_FL_HAS_EVENTS))
			return -ENOIOCTLCMD;

		return v4l2_event_dequeue(vfh, arg, file->f_flags & O_NONBLOCK);

	case VIDIOC_SUBSCRIBE_EVENT:
		return v4l2_subdev_call(sd, core, subscribe_event, vfh, arg);

	case VIDIOC_UNSUBSCRIBE_EVENT:
		return v4l2_subdev_call(sd, core, unsubscribe_event, vfh, arg);

#ifdef CONFIG_VIDEO_ADV_DEBUG
	case VIDIOC_DBG_G_REGISTER:
	{
		struct v4l2_dbg_register *p = arg;

		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		return v4l2_subdev_call(sd, core, g_register, p);
	}
	case VIDIOC_DBG_S_REGISTER:
	{
		struct v4l2_dbg_register *p = arg;

		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		return v4l2_subdev_call(sd, core, s_register, p);
	}
	case VIDIOC_DBG_G_CHIP_INFO:
	{
		struct v4l2_dbg_chip_info *p = arg;

		if (p->match.type != V4L2_CHIP_MATCH_SUBDEV || p->match.addr)
			return -EINVAL;
		if (sd->ops->core && sd->ops->core->s_register)
			p->flags |= V4L2_CHIP_FL_WRITABLE;
		if (sd->ops->core && sd->ops->core->g_register)
			p->flags |= V4L2_CHIP_FL_READABLE;
		strlcpy(p->name, sd->name, sizeof(p->name));
		return 0;
	}
#endif

	case VIDIOC_LOG_STATUS: {
		int ret;

		pr_info("%s: =================  START STATUS  =================\n",
			sd->name);
		ret = v4l2_subdev_call(sd, core, log_status);
		pr_info("%s: ==================  END STATUS  ==================\n",
			sd->name);
		return ret;
	}

#if defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	case VIDIOC_SUBDEV_G_FMT: {
		struct v4l2_subdev_format *format = arg;

		rval = check_format(sd, format);
		if (rval)
			return rval;

		memset(format->reserved, 0, sizeof(format->reserved));
		memset(format->format.reserved, 0, sizeof(format->format.reserved));
		return v4l2_subdev_call(sd, pad, get_fmt, subdev_fh->pad, format);
	}

	case VIDIOC_SUBDEV_S_FMT: {
		struct v4l2_subdev_format *format = arg;

		rval = check_format(sd, format);
		if (rval)
			return rval;

		memset(format->reserved, 0, sizeof(format->reserved));
		memset(format->format.reserved, 0, sizeof(format->format.reserved));
		return v4l2_subdev_call(sd, pad, set_fmt, subdev_fh->pad, format);
	}

	case VIDIOC_SUBDEV_G_CROP: {
		struct v4l2_subdev_crop *crop = arg;
		struct v4l2_subdev_selection sel;

		rval = check_crop(sd, crop);
		if (rval)
			return rval;

		memset(crop->reserved, 0, sizeof(crop->reserved));
		memset(&sel, 0, sizeof(sel));
		sel.which = crop->which;
		sel.pad = crop->pad;
		sel.target = V4L2_SEL_TGT_CROP;

		rval = v4l2_subdev_call(
			sd, pad, get_selection, subdev_fh->pad, &sel);

		crop->rect = sel.r;

		return rval;
	}

	case VIDIOC_SUBDEV_S_CROP: {
		struct v4l2_subdev_crop *crop = arg;
		struct v4l2_subdev_selection sel;

		memset(crop->reserved, 0, sizeof(crop->reserved));
		rval = check_crop(sd, crop);
		if (rval)
			return rval;

		memset(&sel, 0, sizeof(sel));
		sel.which = crop->which;
		sel.pad = crop->pad;
		sel.target = V4L2_SEL_TGT_CROP;
		sel.r = crop->rect;

		rval = v4l2_subdev_call(
			sd, pad, set_selection, subdev_fh->pad, &sel);

		crop->rect = sel.r;

		return rval;
	}

	case VIDIOC_SUBDEV_ENUM_MBUS_CODE: {
		struct v4l2_subdev_mbus_code_enum *code = arg;

		if (code->which != V4L2_SUBDEV_FORMAT_TRY &&
		    code->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (code->pad >= sd->entity.num_pads)
			return -EINVAL;

		memset(code->reserved, 0, sizeof(code->reserved));
		return v4l2_subdev_call(sd, pad, enum_mbus_code, subdev_fh->pad,
					code);
	}

	case VIDIOC_SUBDEV_ENUM_FRAME_SIZE: {
		struct v4l2_subdev_frame_size_enum *fse = arg;

		if (fse->which != V4L2_SUBDEV_FORMAT_TRY &&
		    fse->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (fse->pad >= sd->entity.num_pads)
			return -EINVAL;

		memset(fse->reserved, 0, sizeof(fse->reserved));
		return v4l2_subdev_call(sd, pad, enum_frame_size, subdev_fh->pad,
					fse);
	}

	case VIDIOC_SUBDEV_G_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval *fi = arg;

		if (fi->pad >= sd->entity.num_pads)
			return -EINVAL;

		memset(fi->reserved, 0, sizeof(fi->reserved));
		return v4l2_subdev_call(sd, video, g_frame_interval, arg);
	}

	case VIDIOC_SUBDEV_S_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval *fi = arg;

		if (fi->pad >= sd->entity.num_pads)
			return -EINVAL;

		memset(fi->reserved, 0, sizeof(fi->reserved));
		return v4l2_subdev_call(sd, video, s_frame_interval, arg);
	}

	case VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval_enum *fie = arg;

		if (fie->which != V4L2_SUBDEV_FORMAT_TRY &&
		    fie->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (fie->pad >= sd->entity.num_pads)
			return -EINVAL;

		memset(fie->reserved, 0, sizeof(fie->reserved));
		return v4l2_subdev_call(sd, pad, enum_frame_interval, subdev_fh->pad,
					fie);
	}

	case VIDIOC_SUBDEV_G_SELECTION: {
		struct v4l2_subdev_selection *sel = arg;

		rval = check_selection(sd, sel);
		if (rval)
			return rval;

		memset(sel->reserved, 0, sizeof(sel->reserved));
		return v4l2_subdev_call(
			sd, pad, get_selection, subdev_fh->pad, sel);
	}

	case VIDIOC_SUBDEV_S_SELECTION: {
		struct v4l2_subdev_selection *sel = arg;

		rval = check_selection(sd, sel);
		if (rval)
			return rval;

		memset(sel->reserved, 0, sizeof(sel->reserved));
		return v4l2_subdev_call(
			sd, pad, set_selection, subdev_fh->pad, sel);
	}

	case VIDIOC_G_EDID: {
		struct v4l2_subdev_edid *edid = arg;

		rval = check_edid(sd, edid);
		if (rval)
			return rval;

		return v4l2_subdev_call(sd, pad, get_edid, edid);
	}

	case VIDIOC_S_EDID: {
		struct v4l2_subdev_edid *edid = arg;

		rval = check_edid(sd, edid);
		if (rval)
			return rval;

		return v4l2_subdev_call(sd, pad, set_edid, edid);
	}

	case VIDIOC_SUBDEV_DV_TIMINGS_CAP: {
		struct v4l2_dv_timings_cap *cap = arg;

		if (cap->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, dv_timings_cap, cap);
	}

	case VIDIOC_SUBDEV_ENUM_DV_TIMINGS: {
		struct v4l2_enum_dv_timings *dvt = arg;

		if (dvt->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, enum_dv_timings, dvt);
	}

	case VIDIOC_SUBDEV_QUERY_DV_TIMINGS:
		return v4l2_subdev_call(sd, video, query_dv_timings, arg);

	case VIDIOC_SUBDEV_G_DV_TIMINGS:
		return v4l2_subdev_call(sd, video, g_dv_timings, arg);

	case VIDIOC_SUBDEV_S_DV_TIMINGS:
		return v4l2_subdev_call(sd, video, s_dv_timings, arg);

	case VIDIOC_SUBDEV_G_STD:
		return v4l2_subdev_call(sd, video, g_std, arg);

	case VIDIOC_SUBDEV_S_STD: {
		v4l2_std_id *std = arg;

		return v4l2_subdev_call(sd, video, s_std, *std);
	}

	case VIDIOC_SUBDEV_ENUMSTD: {
		struct v4l2_standard *p = arg;
		v4l2_std_id id;

		if (v4l2_subdev_call(sd, video, g_tvnorms, &id))
			return -EINVAL;

		return v4l_video_std_enumstd(p, id);
	}

	case VIDIOC_SUBDEV_QUERYSTD:
		return v4l2_subdev_call(sd, video, querystd, arg);
#endif
	default:
		return v4l2_subdev_call(sd, core, ioctl, cmd, arg);
	}

	return 0;
}