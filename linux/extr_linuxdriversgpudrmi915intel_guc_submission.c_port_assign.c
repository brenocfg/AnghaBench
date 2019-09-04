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
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_get (struct i915_request*) ; 
 int /*<<< orphan*/  port_isset (struct execlist_port*) ; 
 int /*<<< orphan*/  port_set (struct execlist_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_assign(struct execlist_port *port, struct i915_request *rq)
{
	GEM_BUG_ON(port_isset(port));

	port_set(port, i915_request_get(rq));
}