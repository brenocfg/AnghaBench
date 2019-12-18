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
struct tb_path_hop {int path_length; struct tb_path_hop* hops; int /*<<< orphan*/  next_hop_index; scalar_t__ out_port; int /*<<< orphan*/  in_hop_index; scalar_t__ in_port; } ;
struct tb_path {int path_length; struct tb_path* hops; int /*<<< orphan*/  next_hop_index; scalar_t__ out_port; int /*<<< orphan*/  in_hop_index; scalar_t__ in_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tb_path_hop*) ; 
 int /*<<< orphan*/  tb_port_release_in_hopid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_port_release_out_hopid (scalar_t__,int /*<<< orphan*/ ) ; 

void tb_path_free(struct tb_path *path)
{
	int i;

	for (i = 0; i < path->path_length; i++) {
		const struct tb_path_hop *hop = &path->hops[i];

		if (hop->in_port)
			tb_port_release_in_hopid(hop->in_port,
						 hop->in_hop_index);
		if (hop->out_port)
			tb_port_release_out_hopid(hop->out_port,
						  hop->next_hop_index);
	}

	kfree(path->hops);
	kfree(path);
}