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
struct rdma_restrack_entry {int user; int /*<<< orphan*/ * task; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_restrack_add (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/  set_kern_name (struct rdma_restrack_entry*) ; 

void rdma_restrack_kadd(struct rdma_restrack_entry *res)
{
	res->task = NULL;
	set_kern_name(res);
	res->user = false;
	rdma_restrack_add(res);
}