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
struct v4l2_fwnode_link {int /*<<< orphan*/  remote_node; int /*<<< orphan*/  local_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 

void v4l2_fwnode_put_link(struct v4l2_fwnode_link *link)
{
	fwnode_handle_put(link->local_node);
	fwnode_handle_put(link->remote_node);
}