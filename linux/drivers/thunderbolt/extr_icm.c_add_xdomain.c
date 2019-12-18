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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct tb_xdomain {void* depth; void* link; } ;
struct tb_switch {int /*<<< orphan*/  dev; int /*<<< orphan*/  tb; } ;
struct TYPE_2__ {struct tb_xdomain* xdomain; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 TYPE_1__* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int /*<<< orphan*/  tb_xdomain_add (struct tb_xdomain*) ; 
 struct tb_xdomain* tb_xdomain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void add_xdomain(struct tb_switch *sw, u64 route,
			const uuid_t *local_uuid, const uuid_t *remote_uuid,
			u8 link, u8 depth)
{
	struct tb_xdomain *xd;

	pm_runtime_get_sync(&sw->dev);

	xd = tb_xdomain_alloc(sw->tb, &sw->dev, route, local_uuid, remote_uuid);
	if (!xd)
		goto out;

	xd->link = link;
	xd->depth = depth;

	tb_port_at(route, sw)->xdomain = xd;

	tb_xdomain_add(xd);

out:
	pm_runtime_mark_last_busy(&sw->dev);
	pm_runtime_put_autosuspend(&sw->dev);
}