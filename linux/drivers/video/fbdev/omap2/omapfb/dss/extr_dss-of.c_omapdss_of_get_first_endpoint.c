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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* omapdss_of_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* omapdss_of_get_next_port (struct device_node const*,int /*<<< orphan*/ *) ; 

struct device_node *
omapdss_of_get_first_endpoint(const struct device_node *parent)
{
	struct device_node *port, *ep;

	port = omapdss_of_get_next_port(parent, NULL);

	if (!port)
		return NULL;

	ep = omapdss_of_get_next_endpoint(port, NULL);

	of_node_put(port);

	return ep;
}