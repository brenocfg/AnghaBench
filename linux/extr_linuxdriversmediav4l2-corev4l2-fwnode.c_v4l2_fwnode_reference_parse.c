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
struct v4l2_async_subdev {int /*<<< orphan*/  match_type; TYPE_1__ match; } ;
struct v4l2_async_notifier {size_t num_subdevs; size_t max_subdevs; struct v4l2_async_subdev** subdevs; } ;
struct fwnode_reference_args {int /*<<< orphan*/  fwnode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int fwnode_property_get_reference_args (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,struct fwnode_reference_args*) ; 
 struct v4l2_async_subdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_realloc (struct v4l2_async_notifier*,size_t) ; 

__attribute__((used)) static int v4l2_fwnode_reference_parse(
	struct device *dev, struct v4l2_async_notifier *notifier,
	const char *prop)
{
	struct fwnode_reference_args args;
	unsigned int index;
	int ret;

	for (index = 0;
	     !(ret = fwnode_property_get_reference_args(
		       dev_fwnode(dev), prop, NULL, 0, index, &args));
	     index++)
		fwnode_handle_put(args.fwnode);

	if (!index)
		return -ENOENT;

	/*
	 * Note that right now both -ENODATA and -ENOENT may signal
	 * out-of-bounds access. Return the error in cases other than that.
	 */
	if (ret != -ENOENT && ret != -ENODATA)
		return ret;

	ret = v4l2_async_notifier_realloc(notifier,
					  notifier->num_subdevs + index);
	if (ret)
		return ret;

	for (index = 0; !fwnode_property_get_reference_args(
		     dev_fwnode(dev), prop, NULL, 0, index, &args);
	     index++) {
		struct v4l2_async_subdev *asd;

		if (WARN_ON(notifier->num_subdevs >= notifier->max_subdevs)) {
			ret = -EINVAL;
			goto error;
		}

		asd = kzalloc(sizeof(*asd), GFP_KERNEL);
		if (!asd) {
			ret = -ENOMEM;
			goto error;
		}

		notifier->subdevs[notifier->num_subdevs] = asd;
		asd->match.fwnode = args.fwnode;
		asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
		notifier->num_subdevs++;
	}

	return 0;

error:
	fwnode_handle_put(args.fwnode);
	return ret;
}