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
struct TYPE_2__ {struct fwnode_handle* fwnode; } ;
struct v4l2_async_subdev {int /*<<< orphan*/  match_type; TYPE_1__ match; } ;
struct v4l2_async_notifier {size_t num_subdevs; size_t max_subdevs; struct v4l2_async_subdev** subdevs; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct fwnode_handle*) ; 
 int PTR_ERR (struct fwnode_handle*) ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 struct v4l2_async_subdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_realloc (struct v4l2_async_notifier*,size_t) ; 
 struct fwnode_handle* v4l2_fwnode_reference_get_int_prop (int /*<<< orphan*/ ,char const*,unsigned int,char const* const*,unsigned int) ; 

__attribute__((used)) static int v4l2_fwnode_reference_parse_int_props(
	struct device *dev, struct v4l2_async_notifier *notifier,
	const char *prop, const char * const *props, unsigned int nprops)
{
	struct fwnode_handle *fwnode;
	unsigned int index;
	int ret;

	index = 0;
	do {
		fwnode = v4l2_fwnode_reference_get_int_prop(dev_fwnode(dev),
							    prop, index,
							    props, nprops);
		if (IS_ERR(fwnode)) {
			/*
			 * Note that right now both -ENODATA and -ENOENT may
			 * signal out-of-bounds access. Return the error in
			 * cases other than that.
			 */
			if (PTR_ERR(fwnode) != -ENOENT &&
			    PTR_ERR(fwnode) != -ENODATA)
				return PTR_ERR(fwnode);
			break;
		}
		fwnode_handle_put(fwnode);
		index++;
	} while (1);

	ret = v4l2_async_notifier_realloc(notifier,
					  notifier->num_subdevs + index);
	if (ret)
		return -ENOMEM;

	for (index = 0; !IS_ERR((fwnode = v4l2_fwnode_reference_get_int_prop(
					 dev_fwnode(dev), prop, index, props,
					 nprops))); index++) {
		struct v4l2_async_subdev *asd;

		if (WARN_ON(notifier->num_subdevs >= notifier->max_subdevs)) {
			ret = -EINVAL;
			goto error;
		}

		asd = kzalloc(sizeof(struct v4l2_async_subdev), GFP_KERNEL);
		if (!asd) {
			ret = -ENOMEM;
			goto error;
		}

		notifier->subdevs[notifier->num_subdevs] = asd;
		asd->match.fwnode = fwnode;
		asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
		notifier->num_subdevs++;
	}

	return PTR_ERR(fwnode) == -ENOENT ? 0 : PTR_ERR(fwnode);

error:
	fwnode_handle_put(fwnode);
	return ret;
}