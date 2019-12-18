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
struct tb_tunnel {int npaths; TYPE_1__** paths; int /*<<< orphan*/  (* activate ) (struct tb_tunnel*,int) ;} ;
struct TYPE_2__ {scalar_t__ activated; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tb_tunnel*,int) ; 
 int /*<<< orphan*/  tb_path_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  tb_tunnel_dbg (struct tb_tunnel*,char*) ; 

void tb_tunnel_deactivate(struct tb_tunnel *tunnel)
{
	int i;

	tb_tunnel_dbg(tunnel, "deactivating\n");

	if (tunnel->activate)
		tunnel->activate(tunnel, false);

	for (i = 0; i < tunnel->npaths; i++) {
		if (tunnel->paths[i] && tunnel->paths[i]->activated)
			tb_path_deactivate(tunnel->paths[i]);
	}
}