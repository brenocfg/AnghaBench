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
struct v4l2_fwnode_endpoint {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int __v4l2_fwnode_endpoint_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int v4l2_fwnode_endpoint_parse(struct fwnode_handle *fwnode,
			       struct v4l2_fwnode_endpoint *vep)
{
	int ret;

	ret = __v4l2_fwnode_endpoint_parse(fwnode, vep);

	pr_debug("===== end V4L2 endpoint properties\n");

	return ret;
}