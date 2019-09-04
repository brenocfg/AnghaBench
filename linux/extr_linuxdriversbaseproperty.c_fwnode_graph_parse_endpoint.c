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
struct fwnode_handle {int dummy; } ;
struct fwnode_endpoint {int dummy; } ;

/* Variables and functions */
 int fwnode_call_int_op (struct fwnode_handle const*,int /*<<< orphan*/ ,struct fwnode_endpoint*) ; 
 int /*<<< orphan*/  graph_parse_endpoint ; 
 int /*<<< orphan*/  memset (struct fwnode_endpoint*,int /*<<< orphan*/ ,int) ; 

int fwnode_graph_parse_endpoint(const struct fwnode_handle *fwnode,
				struct fwnode_endpoint *endpoint)
{
	memset(endpoint, 0, sizeof(*endpoint));

	return fwnode_call_int_op(fwnode, graph_parse_endpoint, endpoint);
}