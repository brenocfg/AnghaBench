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
struct mtu3_ep {int /*<<< orphan*/  gpd_ring; } ;

/* Variables and functions */
 int gpd_ring_empty (int /*<<< orphan*/ *) ; 

int mtu3_prepare_transfer(struct mtu3_ep *mep)
{
	return gpd_ring_empty(&mep->gpd_ring);
}