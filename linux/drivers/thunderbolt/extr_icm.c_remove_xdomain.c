#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct tb_xdomain {int /*<<< orphan*/  route; TYPE_1__ dev; } ;
struct tb_switch {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * xdomain; } ;

/* Variables and functions */
 TYPE_2__* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 struct tb_switch* tb_to_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_xdomain_remove (struct tb_xdomain*) ; 

__attribute__((used)) static void remove_xdomain(struct tb_xdomain *xd)
{
	struct tb_switch *sw;

	sw = tb_to_switch(xd->dev.parent);
	tb_port_at(xd->route, sw)->xdomain = NULL;
	tb_xdomain_remove(xd);
}