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
struct media_request_object {int dummy; } ;
struct v4l2_ctrl_handler {int nr_of_buckets; struct media_request_object req_obj; } ;
struct media_request {scalar_t__ state; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct media_request_object* ERR_CAST (struct media_request*) ; 
 struct media_request_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct media_request*) ; 
 scalar_t__ MEDIA_REQUEST_STATE_UPDATING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct v4l2_ctrl_handler*) ; 
 struct v4l2_ctrl_handler* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct media_request_object* media_request_object_find (struct media_request*,int /*<<< orphan*/ *,struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  media_request_object_get (struct media_request_object*) ; 
 int /*<<< orphan*/  req_ops ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int v4l2_ctrl_request_bind (struct media_request*,struct v4l2_ctrl_handler*,struct v4l2_ctrl_handler*) ; 

__attribute__((used)) static struct media_request_object *
v4l2_ctrls_find_req_obj(struct v4l2_ctrl_handler *hdl,
			struct media_request *req, bool set)
{
	struct media_request_object *obj;
	struct v4l2_ctrl_handler *new_hdl;
	int ret;

	if (IS_ERR(req))
		return ERR_CAST(req);

	if (set && WARN_ON(req->state != MEDIA_REQUEST_STATE_UPDATING))
		return ERR_PTR(-EBUSY);

	obj = media_request_object_find(req, &req_ops, hdl);
	if (obj)
		return obj;
	if (!set)
		return ERR_PTR(-ENOENT);

	new_hdl = kzalloc(sizeof(*new_hdl), GFP_KERNEL);
	if (!new_hdl)
		return ERR_PTR(-ENOMEM);

	obj = &new_hdl->req_obj;
	ret = v4l2_ctrl_handler_init(new_hdl, (hdl->nr_of_buckets - 1) * 8);
	if (!ret)
		ret = v4l2_ctrl_request_bind(req, new_hdl, hdl);
	if (ret) {
		kfree(new_hdl);

		return ERR_PTR(ret);
	}

	media_request_object_get(obj);
	return obj;
}