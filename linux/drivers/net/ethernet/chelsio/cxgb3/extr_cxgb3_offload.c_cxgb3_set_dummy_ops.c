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
struct t3cdev {int /*<<< orphan*/  neigh_update; int /*<<< orphan*/  recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_neigh_update ; 
 int /*<<< orphan*/  rx_offload_blackhole ; 

void cxgb3_set_dummy_ops(struct t3cdev *dev)
{
	dev->recv = rx_offload_blackhole;
	dev->neigh_update = dummy_neigh_update;
}