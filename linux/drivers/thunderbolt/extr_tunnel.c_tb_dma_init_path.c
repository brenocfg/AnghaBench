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
typedef  int /*<<< orphan*/  u32 ;
struct tb_path {unsigned int egress_fc_enable; unsigned int ingress_shared_buffer; int priority; int weight; int clear_fc; int path_length; TYPE_1__* hops; int /*<<< orphan*/  egress_shared_buffer; int /*<<< orphan*/  ingress_fc_enable; } ;
struct TYPE_2__ {int /*<<< orphan*/  initial_credits; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_PATH_ALL ; 
 int /*<<< orphan*/  TB_PATH_NONE ; 

__attribute__((used)) static void tb_dma_init_path(struct tb_path *path, unsigned int isb,
			     unsigned int efc, u32 credits)
{
	int i;

	path->egress_fc_enable = efc;
	path->ingress_fc_enable = TB_PATH_ALL;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_shared_buffer = isb;
	path->priority = 5;
	path->weight = 1;
	path->clear_fc = true;

	for (i = 0; i < path->path_length; i++)
		path->hops[i].initial_credits = credits;
}