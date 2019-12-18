#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct v4l2_async_notifier {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct v4l2_async_subdev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int /*<<< orphan*/  fwnode_handle_get (struct fwnode_handle*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int /*<<< orphan*/  kfree (struct v4l2_async_subdev*) ; 
 struct v4l2_async_subdev* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_add_subdev (struct v4l2_async_notifier*,struct v4l2_async_subdev*) ; 

struct v4l2_async_subdev *
v4l2_async_notifier_add_fwnode_subdev(struct v4l2_async_notifier *notifier,
				      struct fwnode_handle *fwnode,
				      unsigned int asd_struct_size)
{
	struct v4l2_async_subdev *asd;
	int ret;

	asd = kzalloc(asd_struct_size, GFP_KERNEL);
	if (!asd)
		return ERR_PTR(-ENOMEM);

	asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
	asd->match.fwnode = fwnode_handle_get(fwnode);

	ret = v4l2_async_notifier_add_subdev(notifier, asd);
	if (ret) {
		fwnode_handle_put(fwnode);
		kfree(asd);
		return ERR_PTR(ret);
	}

	return asd;
}