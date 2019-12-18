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
struct tb_path {int egress_fc_enable; int priority; int weight; int path_length; TYPE_1__* hops; void* ingress_shared_buffer; int /*<<< orphan*/  ingress_fc_enable; void* egress_shared_buffer; } ;
struct TYPE_2__ {int initial_credits; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_PATH_ALL ; 
 int TB_PATH_INTERNAL ; 
 void* TB_PATH_NONE ; 
 int TB_PATH_SOURCE ; 

__attribute__((used)) static void tb_dp_init_aux_path(struct tb_path *path)
{
	int i;

	path->egress_fc_enable = TB_PATH_SOURCE | TB_PATH_INTERNAL;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_fc_enable = TB_PATH_ALL;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 2;
	path->weight = 1;

	for (i = 0; i < path->path_length; i++)
		path->hops[i].initial_credits = 1;
}