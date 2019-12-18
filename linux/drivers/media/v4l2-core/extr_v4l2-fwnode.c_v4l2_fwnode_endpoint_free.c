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
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  link_frequencies; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void v4l2_fwnode_endpoint_free(struct v4l2_fwnode_endpoint *vep)
{
	if (IS_ERR_OR_NULL(vep))
		return;

	kfree(vep->link_frequencies);
}