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
struct i915_request {int dummy; } ;
struct execlist_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_request_get (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  port_count (struct execlist_port*) ; 
 scalar_t__ port_isset (struct execlist_port*) ; 
 int /*<<< orphan*/  port_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_request* port_request (struct execlist_port*) ; 
 int /*<<< orphan*/  port_set (struct execlist_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_assign(struct execlist_port *port, struct i915_request *rq)
{
	GEM_BUG_ON(rq == port_request(port));

	if (port_isset(port))
		i915_request_put(port_request(port));

	port_set(port, port_pack(i915_request_get(rq), port_count(port)));
}