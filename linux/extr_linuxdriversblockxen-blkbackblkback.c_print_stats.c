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
struct xen_blkif_ring {scalar_t__ st_ds_req; scalar_t__ st_oo_req; scalar_t__ st_wr_req; scalar_t__ st_rd_req; scalar_t__ st_print; int /*<<< orphan*/  persistent_gnt_c; int /*<<< orphan*/  st_f_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_blkif_max_pgrants ; 

__attribute__((used)) static void print_stats(struct xen_blkif_ring *ring)
{
	pr_info("(%s): oo %3llu  |  rd %4llu  |  wr %4llu  |  f %4llu"
		 "  |  ds %4llu | pg: %4u/%4d\n",
		 current->comm, ring->st_oo_req,
		 ring->st_rd_req, ring->st_wr_req,
		 ring->st_f_req, ring->st_ds_req,
		 ring->persistent_gnt_c,
		 xen_blkif_max_pgrants);
	ring->st_print = jiffies + msecs_to_jiffies(10 * 1000);
	ring->st_rd_req = 0;
	ring->st_wr_req = 0;
	ring->st_oo_req = 0;
	ring->st_ds_req = 0;
}