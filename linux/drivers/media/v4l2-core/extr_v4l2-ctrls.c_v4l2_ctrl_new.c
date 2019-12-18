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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_ctrl_vp8_frame_header {int dummy; } ;
struct v4l2_ctrl_type_ops {int /*<<< orphan*/  (* init ) (struct v4l2_ctrl*,unsigned int,TYPE_2__) ;} ;
struct v4l2_ctrl_ops {int dummy; } ;
struct v4l2_ctrl_mpeg2_slice_params {int dummy; } ;
struct v4l2_ctrl_mpeg2_quantization {int dummy; } ;
struct v4l2_ctrl_handler {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrls; scalar_t__ error; } ;
struct v4l2_ctrl_h264_sps {int dummy; } ;
struct v4l2_ctrl_h264_slice_params {int dummy; } ;
struct v4l2_ctrl_h264_scaling_matrix {int dummy; } ;
struct v4l2_ctrl_h264_pps {int dummy; } ;
struct v4l2_ctrl_h264_decode_params {int dummy; } ;
struct v4l2_ctrl_fwht_params {int dummy; } ;
struct TYPE_5__ {void** p; } ;
struct TYPE_4__ {void* val; } ;
struct v4l2_ctrl {unsigned int id; char const* name; int type; unsigned int flags; int is_string; int is_ptr; int is_int; int is_array; unsigned int elems; unsigned int nr_of_dims; unsigned int elem_size; char const* const* qmenu; void* const* qmenu_int; int /*<<< orphan*/  node; TYPE_2__ p_new; struct v4l2_ctrl_type_ops const* type_ops; TYPE_2__ p_cur; TYPE_1__ cur; void* val; void* priv; int /*<<< orphan*/  dims; void* default_value; int /*<<< orphan*/  step; void* maximum; void* minimum; struct v4l2_ctrl_ops const* ops; struct v4l2_ctrl_handler* handler; int /*<<< orphan*/  ev_subs; } ;
typedef  void* s64 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum v4l2_ctrl_type { ____Placeholder_v4l2_ctrl_type } v4l2_ctrl_type ;
typedef  int /*<<< orphan*/  dims ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int V4L2_CID_PRIVATE_BASE ; 
 int V4L2_CTRL_COMPOUND_TYPES ; 
 unsigned int V4L2_CTRL_FLAG_EXECUTE_ON_WRITE ; 
 unsigned int V4L2_CTRL_FLAG_READ_ONLY ; 
 unsigned int V4L2_CTRL_FLAG_WRITE_ONLY ; 
 unsigned int V4L2_CTRL_MAX_DIMS ; 
 int V4L2_CTRL_TYPE_BUTTON ; 
 int V4L2_CTRL_TYPE_CTRL_CLASS ; 
#define  V4L2_CTRL_TYPE_FWHT_PARAMS 141 
#define  V4L2_CTRL_TYPE_H264_DECODE_PARAMS 140 
#define  V4L2_CTRL_TYPE_H264_PPS 139 
#define  V4L2_CTRL_TYPE_H264_SCALING_MATRIX 138 
#define  V4L2_CTRL_TYPE_H264_SLICE_PARAMS 137 
#define  V4L2_CTRL_TYPE_H264_SPS 136 
#define  V4L2_CTRL_TYPE_INTEGER64 135 
 int V4L2_CTRL_TYPE_INTEGER_MENU ; 
 int V4L2_CTRL_TYPE_MENU ; 
#define  V4L2_CTRL_TYPE_MPEG2_QUANTIZATION 134 
#define  V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS 133 
#define  V4L2_CTRL_TYPE_STRING 132 
#define  V4L2_CTRL_TYPE_U16 131 
#define  V4L2_CTRL_TYPE_U32 130 
#define  V4L2_CTRL_TYPE_U8 129 
#define  V4L2_CTRL_TYPE_VP8_FRAME_HEADER 128 
 int check_range (int,void*,void*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ handler_new_ref (struct v4l2_ctrl_handler*,struct v4l2_ctrl*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  handler_set_err (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  kvfree (struct v4l2_ctrl*) ; 
 struct v4l2_ctrl* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int const*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl_type_ops const std_type_ops ; 
 int /*<<< orphan*/  stub1 (struct v4l2_ctrl*,unsigned int,TYPE_2__) ; 
 int /*<<< orphan*/  stub2 (struct v4l2_ctrl*,unsigned int,TYPE_2__) ; 

__attribute__((used)) static struct v4l2_ctrl *v4l2_ctrl_new(struct v4l2_ctrl_handler *hdl,
			const struct v4l2_ctrl_ops *ops,
			const struct v4l2_ctrl_type_ops *type_ops,
			u32 id, const char *name, enum v4l2_ctrl_type type,
			s64 min, s64 max, u64 step, s64 def,
			const u32 dims[V4L2_CTRL_MAX_DIMS], u32 elem_size,
			u32 flags, const char * const *qmenu,
			const s64 *qmenu_int, void *priv)
{
	struct v4l2_ctrl *ctrl;
	unsigned sz_extra;
	unsigned nr_of_dims = 0;
	unsigned elems = 1;
	bool is_array;
	unsigned tot_ctrl_size;
	unsigned idx;
	void *data;
	int err;

	if (hdl->error)
		return NULL;

	while (dims && dims[nr_of_dims]) {
		elems *= dims[nr_of_dims];
		nr_of_dims++;
		if (nr_of_dims == V4L2_CTRL_MAX_DIMS)
			break;
	}
	is_array = nr_of_dims > 0;

	/* Prefill elem_size for all types handled by std_type_ops */
	switch ((u32)type) {
	case V4L2_CTRL_TYPE_INTEGER64:
		elem_size = sizeof(s64);
		break;
	case V4L2_CTRL_TYPE_STRING:
		elem_size = max + 1;
		break;
	case V4L2_CTRL_TYPE_U8:
		elem_size = sizeof(u8);
		break;
	case V4L2_CTRL_TYPE_U16:
		elem_size = sizeof(u16);
		break;
	case V4L2_CTRL_TYPE_U32:
		elem_size = sizeof(u32);
		break;
	case V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS:
		elem_size = sizeof(struct v4l2_ctrl_mpeg2_slice_params);
		break;
	case V4L2_CTRL_TYPE_MPEG2_QUANTIZATION:
		elem_size = sizeof(struct v4l2_ctrl_mpeg2_quantization);
		break;
	case V4L2_CTRL_TYPE_FWHT_PARAMS:
		elem_size = sizeof(struct v4l2_ctrl_fwht_params);
		break;
	case V4L2_CTRL_TYPE_H264_SPS:
		elem_size = sizeof(struct v4l2_ctrl_h264_sps);
		break;
	case V4L2_CTRL_TYPE_H264_PPS:
		elem_size = sizeof(struct v4l2_ctrl_h264_pps);
		break;
	case V4L2_CTRL_TYPE_H264_SCALING_MATRIX:
		elem_size = sizeof(struct v4l2_ctrl_h264_scaling_matrix);
		break;
	case V4L2_CTRL_TYPE_H264_SLICE_PARAMS:
		elem_size = sizeof(struct v4l2_ctrl_h264_slice_params);
		break;
	case V4L2_CTRL_TYPE_H264_DECODE_PARAMS:
		elem_size = sizeof(struct v4l2_ctrl_h264_decode_params);
		break;
	case V4L2_CTRL_TYPE_VP8_FRAME_HEADER:
		elem_size = sizeof(struct v4l2_ctrl_vp8_frame_header);
		break;
	default:
		if (type < V4L2_CTRL_COMPOUND_TYPES)
			elem_size = sizeof(s32);
		break;
	}
	tot_ctrl_size = elem_size * elems;

	/* Sanity checks */
	if (id == 0 || name == NULL || !elem_size ||
	    id >= V4L2_CID_PRIVATE_BASE ||
	    (type == V4L2_CTRL_TYPE_MENU && qmenu == NULL) ||
	    (type == V4L2_CTRL_TYPE_INTEGER_MENU && qmenu_int == NULL)) {
		handler_set_err(hdl, -ERANGE);
		return NULL;
	}
	err = check_range(type, min, max, step, def);
	if (err) {
		handler_set_err(hdl, err);
		return NULL;
	}
	if (is_array &&
	    (type == V4L2_CTRL_TYPE_BUTTON ||
	     type == V4L2_CTRL_TYPE_CTRL_CLASS)) {
		handler_set_err(hdl, -EINVAL);
		return NULL;
	}

	sz_extra = 0;
	if (type == V4L2_CTRL_TYPE_BUTTON)
		flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
	else if (type == V4L2_CTRL_TYPE_CTRL_CLASS)
		flags |= V4L2_CTRL_FLAG_READ_ONLY;
	else if (type == V4L2_CTRL_TYPE_INTEGER64 ||
		 type == V4L2_CTRL_TYPE_STRING ||
		 type >= V4L2_CTRL_COMPOUND_TYPES ||
		 is_array)
		sz_extra += 2 * tot_ctrl_size;

	ctrl = kvzalloc(sizeof(*ctrl) + sz_extra, GFP_KERNEL);
	if (ctrl == NULL) {
		handler_set_err(hdl, -ENOMEM);
		return NULL;
	}

	INIT_LIST_HEAD(&ctrl->node);
	INIT_LIST_HEAD(&ctrl->ev_subs);
	ctrl->handler = hdl;
	ctrl->ops = ops;
	ctrl->type_ops = type_ops ? type_ops : &std_type_ops;
	ctrl->id = id;
	ctrl->name = name;
	ctrl->type = type;
	ctrl->flags = flags;
	ctrl->minimum = min;
	ctrl->maximum = max;
	ctrl->step = step;
	ctrl->default_value = def;
	ctrl->is_string = !is_array && type == V4L2_CTRL_TYPE_STRING;
	ctrl->is_ptr = is_array || type >= V4L2_CTRL_COMPOUND_TYPES || ctrl->is_string;
	ctrl->is_int = !ctrl->is_ptr && type != V4L2_CTRL_TYPE_INTEGER64;
	ctrl->is_array = is_array;
	ctrl->elems = elems;
	ctrl->nr_of_dims = nr_of_dims;
	if (nr_of_dims)
		memcpy(ctrl->dims, dims, nr_of_dims * sizeof(dims[0]));
	ctrl->elem_size = elem_size;
	if (type == V4L2_CTRL_TYPE_MENU)
		ctrl->qmenu = qmenu;
	else if (type == V4L2_CTRL_TYPE_INTEGER_MENU)
		ctrl->qmenu_int = qmenu_int;
	ctrl->priv = priv;
	ctrl->cur.val = ctrl->val = def;
	data = &ctrl[1];

	if (!ctrl->is_int) {
		ctrl->p_new.p = data;
		ctrl->p_cur.p = data + tot_ctrl_size;
	} else {
		ctrl->p_new.p = &ctrl->val;
		ctrl->p_cur.p = &ctrl->cur.val;
	}
	for (idx = 0; idx < elems; idx++) {
		ctrl->type_ops->init(ctrl, idx, ctrl->p_cur);
		ctrl->type_ops->init(ctrl, idx, ctrl->p_new);
	}

	if (handler_new_ref(hdl, ctrl, NULL, false, false)) {
		kvfree(ctrl);
		return NULL;
	}
	mutex_lock(hdl->lock);
	list_add_tail(&ctrl->node, &hdl->ctrls);
	mutex_unlock(hdl->lock);
	return ctrl;
}