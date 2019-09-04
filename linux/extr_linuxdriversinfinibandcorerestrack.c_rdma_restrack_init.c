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
struct rdma_restrack_root {int /*<<< orphan*/  fill_res_entry; int /*<<< orphan*/  rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_res_noop ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 

void rdma_restrack_init(struct rdma_restrack_root *res)
{
	init_rwsem(&res->rwsem);
	res->fill_res_entry = fill_res_noop;
}