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
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct video_device {int dummy; } ;
typedef  void v4l2_subdev_selection ;
typedef  void v4l2_subdev_mbus_code_enum ;
typedef  void v4l2_subdev_frame_size_enum ;
typedef  void v4l2_subdev_frame_interval_enum ;
struct v4l2_subdev_frame_interval {void* reserved; } ;
typedef  void v4l2_subdev_format ;
struct v4l2_subdev_fh {unsigned int pad; } ;
struct v4l2_subdev_edid {int dummy; } ;
struct v4l2_subdev_crop {void* reserved; int /*<<< orphan*/  rect; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int flags; int /*<<< orphan*/  name; TYPE_4__* ops; TYPE_1__* v4l2_dev; } ;
struct v4l2_standard {int dummy; } ;
struct v4l2_fh {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_enum_dv_timings {int dummy; } ;
struct v4l2_dv_timings_cap {int dummy; } ;
struct v4l2_dbg_register {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct v4l2_dbg_chip_info {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; TYPE_2__ match; } ;
struct file {int f_flags; struct v4l2_fh* private_data; } ;
typedef  int /*<<< orphan*/  sel ;
struct TYPE_10__ {void* reserved; } ;
struct TYPE_9__ {TYPE_3__* core; } ;
struct TYPE_8__ {int /*<<< orphan*/  g_register; int /*<<< orphan*/  s_register; } ;
struct TYPE_6__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EINVAL ; 
 long ENOIOCTLCMD ; 
 long ENOTTY ; 
 long EPERM ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  V4L2_CHIP_FL_READABLE ; 
 int /*<<< orphan*/  V4L2_CHIP_FL_WRITABLE ; 
 int /*<<< orphan*/  V4L2_CHIP_MATCH_SUBDEV ; 
 void* V4L2_SEL_TGT_CROP ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
#define  VIDIOC_DBG_G_CHIP_INFO 164 
#define  VIDIOC_DBG_G_REGISTER 163 
#define  VIDIOC_DBG_S_REGISTER 162 
#define  VIDIOC_DQEVENT 161 
#define  VIDIOC_G_CTRL 160 
#define  VIDIOC_G_EDID 159 
#define  VIDIOC_G_EXT_CTRLS 158 
#define  VIDIOC_LOG_STATUS 157 
#define  VIDIOC_QUERYCTRL 156 
#define  VIDIOC_QUERYMENU 155 
#define  VIDIOC_QUERY_EXT_CTRL 154 
#define  VIDIOC_SUBDEV_DV_TIMINGS_CAP 153 
#define  VIDIOC_SUBDEV_ENUMSTD 152 
#define  VIDIOC_SUBDEV_ENUM_DV_TIMINGS 151 
#define  VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL 150 
#define  VIDIOC_SUBDEV_ENUM_FRAME_SIZE 149 
#define  VIDIOC_SUBDEV_ENUM_MBUS_CODE 148 
#define  VIDIOC_SUBDEV_G_CROP 147 
#define  VIDIOC_SUBDEV_G_DV_TIMINGS 146 
#define  VIDIOC_SUBDEV_G_FMT 145 
#define  VIDIOC_SUBDEV_G_FRAME_INTERVAL 144 
#define  VIDIOC_SUBDEV_G_SELECTION 143 
#define  VIDIOC_SUBDEV_G_STD 142 
#define  VIDIOC_SUBDEV_QUERYSTD 141 
#define  VIDIOC_SUBDEV_QUERY_DV_TIMINGS 140 
#define  VIDIOC_SUBDEV_S_CROP 139 
#define  VIDIOC_SUBDEV_S_DV_TIMINGS 138 
#define  VIDIOC_SUBDEV_S_FMT 137 
#define  VIDIOC_SUBDEV_S_FRAME_INTERVAL 136 
#define  VIDIOC_SUBDEV_S_SELECTION 135 
#define  VIDIOC_SUBDEV_S_STD 134 
#define  VIDIOC_SUBSCRIBE_EVENT 133 
#define  VIDIOC_S_CTRL 132 
#define  VIDIOC_S_EDID 131 
#define  VIDIOC_S_EXT_CTRLS 130 
#define  VIDIOC_TRY_EXT_CTRLS 129 
#define  VIDIOC_UNSUBSCRIBE_EVENT 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  dv_timings_cap ; 
 int /*<<< orphan*/  enum_dv_timings ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 int /*<<< orphan*/  enum_frame_size ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 int /*<<< orphan*/  g_dv_timings ; 
 int /*<<< orphan*/  g_frame_interval ; 
 int /*<<< orphan*/  g_register ; 
 int /*<<< orphan*/  g_std ; 
 int /*<<< orphan*/  g_tvnorms ; 
 int /*<<< orphan*/  get_edid ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  get_selection ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_dv_timings ; 
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  s_dv_timings ; 
 int /*<<< orphan*/  s_frame_interval ; 
 int /*<<< orphan*/  s_register ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  set_edid ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  set_selection ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  subscribe_event ; 
 struct v4l2_subdev_fh* to_v4l2_subdev_fh (struct v4l2_fh*) ; 
 int /*<<< orphan*/  unsubscribe_event ; 
 long v4l2_event_dequeue (struct v4l2_fh*,void*,int) ; 
 long v4l2_g_ctrl (int /*<<< orphan*/ ,void*) ; 
 long v4l2_g_ext_ctrls (int /*<<< orphan*/ ,struct video_device*,int /*<<< orphan*/ ,void*) ; 
 long v4l2_query_ext_ctrl (int /*<<< orphan*/ ,void*) ; 
 long v4l2_queryctrl (int /*<<< orphan*/ ,void*) ; 
 long v4l2_querymenu (int /*<<< orphan*/ ,void*) ; 
 long v4l2_s_ctrl (struct v4l2_fh*,int /*<<< orphan*/ ,void*) ; 
 long v4l2_s_ext_ctrls (struct v4l2_fh*,int /*<<< orphan*/ ,struct video_device*,int /*<<< orphan*/ ,void*) ; 
 long v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 long v4l2_try_ext_ctrls (int /*<<< orphan*/ ,struct video_device*,int /*<<< orphan*/ ,void*) ; 
 long v4l_video_std_enumstd (struct v4l2_standard*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* vdev_to_v4l2_subdev (struct video_device*) ; 
 int /*<<< orphan*/  video ; 
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
		return v4l2_g_ext_ctrls(vfh->ctrl_handler,
					vdev, sd->v4l2_dev->mdev, arg);

	case VIDIOC_S_EXT_CTRLS:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_s_ext_ctrls(vfh, vfh->ctrl_handler,
					vdev, sd->v4l2_dev->mdev, arg);

	case VIDIOC_TRY_EXT_CTRLS:
		if (!vfh->ctrl_handler)
			return -ENOTTY;
		return v4l2_try_ext_ctrls(vfh->ctrl_handler,
					  vdev, sd->v4l2_dev->mdev, arg);

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
		strscpy(p->name, sd->name, sizeof(p->name));
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

		memset(format->reserved, 0, sizeof(format->reserved));
		memset(format->format.reserved, 0, sizeof(format->format.reserved));
		return v4l2_subdev_call(sd, pad, get_fmt, subdev_fh->pad, format);
	}

	case VIDIOC_SUBDEV_S_FMT: {
		struct v4l2_subdev_format *format = arg;

		memset(format->reserved, 0, sizeof(format->reserved));
		memset(format->format.reserved, 0, sizeof(format->format.reserved));
		return v4l2_subdev_call(sd, pad, set_fmt, subdev_fh->pad, format);
	}

	case VIDIOC_SUBDEV_G_CROP: {
		struct v4l2_subdev_crop *crop = arg;
		struct v4l2_subdev_selection sel;

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

		memset(code->reserved, 0, sizeof(code->reserved));
		return v4l2_subdev_call(sd, pad, enum_mbus_code, subdev_fh->pad,
					code);
	}

	case VIDIOC_SUBDEV_ENUM_FRAME_SIZE: {
		struct v4l2_subdev_frame_size_enum *fse = arg;

		memset(fse->reserved, 0, sizeof(fse->reserved));
		return v4l2_subdev_call(sd, pad, enum_frame_size, subdev_fh->pad,
					fse);
	}

	case VIDIOC_SUBDEV_G_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval *fi = arg;

		memset(fi->reserved, 0, sizeof(fi->reserved));
		return v4l2_subdev_call(sd, video, g_frame_interval, arg);
	}

	case VIDIOC_SUBDEV_S_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval *fi = arg;

		memset(fi->reserved, 0, sizeof(fi->reserved));
		return v4l2_subdev_call(sd, video, s_frame_interval, arg);
	}

	case VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval_enum *fie = arg;

		memset(fie->reserved, 0, sizeof(fie->reserved));
		return v4l2_subdev_call(sd, pad, enum_frame_interval, subdev_fh->pad,
					fie);
	}

	case VIDIOC_SUBDEV_G_SELECTION: {
		struct v4l2_subdev_selection *sel = arg;

		memset(sel->reserved, 0, sizeof(sel->reserved));
		return v4l2_subdev_call(
			sd, pad, get_selection, subdev_fh->pad, sel);
	}

	case VIDIOC_SUBDEV_S_SELECTION: {
		struct v4l2_subdev_selection *sel = arg;

		memset(sel->reserved, 0, sizeof(sel->reserved));
		return v4l2_subdev_call(
			sd, pad, set_selection, subdev_fh->pad, sel);
	}

	case VIDIOC_G_EDID: {
		struct v4l2_subdev_edid *edid = arg;

		return v4l2_subdev_call(sd, pad, get_edid, edid);
	}

	case VIDIOC_S_EDID: {
		struct v4l2_subdev_edid *edid = arg;

		return v4l2_subdev_call(sd, pad, set_edid, edid);
	}

	case VIDIOC_SUBDEV_DV_TIMINGS_CAP: {
		struct v4l2_dv_timings_cap *cap = arg;

		return v4l2_subdev_call(sd, pad, dv_timings_cap, cap);
	}

	case VIDIOC_SUBDEV_ENUM_DV_TIMINGS: {
		struct v4l2_enum_dv_timings *dvt = arg;

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