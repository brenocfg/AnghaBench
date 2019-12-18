#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tb_path {int activated; int path_length; TYPE_3__* hops; int /*<<< orphan*/  name; int /*<<< orphan*/  tb; } ;
struct TYPE_6__ {TYPE_2__* out_port; TYPE_1__* in_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  sw; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tb_path_deactivate_hops (struct tb_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tb_path_deallocate_nfc (struct tb_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tb_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_route (int /*<<< orphan*/ ) ; 

void tb_path_deactivate(struct tb_path *path)
{
	if (!path->activated) {
		tb_WARN(path->tb, "trying to deactivate an inactive path\n");
		return;
	}
	tb_dbg(path->tb,
	       "deactivating %s path from %llx:%x to %llx:%x\n",
	       path->name, tb_route(path->hops[0].in_port->sw),
	       path->hops[0].in_port->port,
	       tb_route(path->hops[path->path_length - 1].out_port->sw),
	       path->hops[path->path_length - 1].out_port->port);
	__tb_path_deactivate_hops(path, 0);
	__tb_path_deallocate_nfc(path, 0);
	path->activated = false;
}