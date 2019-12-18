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
struct tb_path {int path_length; TYPE_1__* hops; int /*<<< orphan*/  clear_fc; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_hop_index; int /*<<< orphan*/  in_port; } ;

/* Variables and functions */
 int ENODEV ; 
 int __tb_path_deactivate_hop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_port_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __tb_path_deactivate_hops(struct tb_path *path, int first_hop)
{
	int i, res;

	for (i = first_hop; i < path->path_length; i++) {
		res = __tb_path_deactivate_hop(path->hops[i].in_port,
					       path->hops[i].in_hop_index,
					       path->clear_fc);
		if (res && res != -ENODEV)
			tb_port_warn(path->hops[i].in_port,
				     "hop deactivation failed for hop %d, index %d\n",
				     i, path->hops[i].in_hop_index);
	}
}