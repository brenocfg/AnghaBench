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
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct fwnode_reference_args {int /*<<< orphan*/  fwnode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODATA ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct v4l2_async_subdev*) ; 
 int PTR_ERR (struct v4l2_async_subdev*) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int fwnode_property_get_reference_args (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,struct fwnode_reference_args*) ; 
 struct v4l2_async_subdev* v4l2_async_notifier_add_fwnode_subdev (struct v4l2_async_notifier*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int v4l2_fwnode_reference_parse(struct device *dev,
				       struct v4l2_async_notifier *notifier,
				       const char *prop)
{
	struct fwnode_reference_args args;
	unsigned int index;
	int ret;

	for (index = 0;
	     !(ret = fwnode_property_get_reference_args(dev_fwnode(dev),
							prop, NULL, 0,
							index, &args));
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

	for (index = 0;
	     !fwnode_property_get_reference_args(dev_fwnode(dev), prop, NULL,
						 0, index, &args);
	     index++) {
		struct v4l2_async_subdev *asd;

		asd = v4l2_async_notifier_add_fwnode_subdev(notifier,
							    args.fwnode,
							    sizeof(*asd));
		fwnode_handle_put(args.fwnode);
		if (IS_ERR(asd)) {
			/* not an error if asd already exists */
			if (PTR_ERR(asd) == -EEXIST)
				continue;

			return PTR_ERR(asd);
		}
	}

	return 0;
}