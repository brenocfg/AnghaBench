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
struct tb_tunnel {int npaths; TYPE_1__** paths; } ;
struct TYPE_2__ {scalar_t__ activated; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tb_tunnel_WARN (struct tb_tunnel*,char*) ; 
 int tb_tunnel_restart (struct tb_tunnel*) ; 

int tb_tunnel_activate(struct tb_tunnel *tunnel)
{
	int i;

	for (i = 0; i < tunnel->npaths; i++) {
		if (tunnel->paths[i]->activated) {
			tb_tunnel_WARN(tunnel,
				       "trying to activate an already activated tunnel\n");
			return -EINVAL;
		}
	}

	return tb_tunnel_restart(tunnel);
}