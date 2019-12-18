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
struct v4l2_fwnode_int_props {char* name; char** props; unsigned int nprops; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
typedef  struct v4l2_async_subdev fwnode_handle ;
struct device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODATA ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct v4l2_async_subdev*) ; 
 int PTR_ERR (struct v4l2_async_subdev*) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct v4l2_async_subdev*) ; 
 struct v4l2_async_subdev* v4l2_async_notifier_add_fwnode_subdev (struct v4l2_async_notifier*,struct v4l2_async_subdev*,int) ; 
 struct v4l2_async_subdev* v4l2_fwnode_reference_get_int_prop (int /*<<< orphan*/ ,char const*,unsigned int,char const* const*,unsigned int) ; 

__attribute__((used)) static int
v4l2_fwnode_reference_parse_int_props(struct device *dev,
				      struct v4l2_async_notifier *notifier,
				      const struct v4l2_fwnode_int_props *p)
{
	struct fwnode_handle *fwnode;
	unsigned int index;
	int ret;
	const char *prop = p->name;
	const char * const *props = p->props;
	unsigned int nprops = p->nprops;

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

	for (index = 0;
	     !IS_ERR((fwnode = v4l2_fwnode_reference_get_int_prop(dev_fwnode(dev),
								  prop, index,
								  props,
								  nprops)));
	     index++) {
		struct v4l2_async_subdev *asd;

		asd = v4l2_async_notifier_add_fwnode_subdev(notifier, fwnode,
							    sizeof(*asd));
		fwnode_handle_put(fwnode);
		if (IS_ERR(asd)) {
			ret = PTR_ERR(asd);
			/* not an error if asd already exists */
			if (ret == -EEXIST)
				continue;

			return PTR_ERR(asd);
		}
	}

	return !fwnode || PTR_ERR(fwnode) == -ENOENT ? 0 : PTR_ERR(fwnode);
}