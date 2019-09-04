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
struct v4l2_fwnode_endpoint {int nr_of_link_frequencies; int /*<<< orphan*/ * link_frequencies; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct v4l2_fwnode_endpoint* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fwnode_property_read_u64_array (struct fwnode_handle*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct v4l2_fwnode_endpoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_free (struct v4l2_fwnode_endpoint*) ; 
 int v4l2_fwnode_endpoint_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 

struct v4l2_fwnode_endpoint *v4l2_fwnode_endpoint_alloc_parse(
	struct fwnode_handle *fwnode)
{
	struct v4l2_fwnode_endpoint *vep;
	int rval;

	vep = kzalloc(sizeof(*vep), GFP_KERNEL);
	if (!vep)
		return ERR_PTR(-ENOMEM);

	rval = v4l2_fwnode_endpoint_parse(fwnode, vep);
	if (rval < 0)
		goto out_err;

	rval = fwnode_property_read_u64_array(fwnode, "link-frequencies",
					      NULL, 0);
	if (rval > 0) {
		vep->link_frequencies =
			kmalloc_array(rval, sizeof(*vep->link_frequencies),
				      GFP_KERNEL);
		if (!vep->link_frequencies) {
			rval = -ENOMEM;
			goto out_err;
		}

		vep->nr_of_link_frequencies = rval;

		rval = fwnode_property_read_u64_array(
			fwnode, "link-frequencies", vep->link_frequencies,
			vep->nr_of_link_frequencies);
		if (rval < 0)
			goto out_err;
	}

	return vep;

out_err:
	v4l2_fwnode_endpoint_free(vep);
	return ERR_PTR(rval);
}