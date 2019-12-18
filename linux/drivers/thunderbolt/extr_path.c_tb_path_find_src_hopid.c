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
struct TYPE_2__ {int max_in_hop_id; } ;
typedef  struct tb_port {TYPE_1__ config; } const tb_port ;

/* Variables and functions */
 int TB_PATH_MIN_HOPID ; 
 struct tb_port const* tb_path_find_dst_port (struct tb_port const*,int,int) ; 

__attribute__((used)) static int tb_path_find_src_hopid(struct tb_port *src,
	const struct tb_port *dst, int dst_hopid)
{
	struct tb_port *out;
	int i;

	for (i = TB_PATH_MIN_HOPID; i <= src->config.max_in_hop_id; i++) {
		out = tb_path_find_dst_port(src, i, dst_hopid);
		if (out == dst)
			return i;
	}

	return 0;
}