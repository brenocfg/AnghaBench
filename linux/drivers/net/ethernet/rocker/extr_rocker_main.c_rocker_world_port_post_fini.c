#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rocker_world_ops {int /*<<< orphan*/  (* port_post_fini ) (struct rocker_port*) ;} ;
struct rocker_port {int /*<<< orphan*/  wpriv; TYPE_1__* rocker; } ;
struct TYPE_2__ {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rocker_port*) ; 

__attribute__((used)) static void rocker_world_port_post_fini(struct rocker_port *rocker_port)
{
	struct rocker_world_ops *wops = rocker_port->rocker->wops;

	if (!wops->port_post_fini)
		return;
	wops->port_post_fini(rocker_port);
	kfree(rocker_port->wpriv);
}