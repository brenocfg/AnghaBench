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
struct sky2_port {TYPE_1__* netdev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 unsigned int roundup (scalar_t__,int) ; 

__attribute__((used)) static unsigned sky2_get_rx_threshold(struct sky2_port *sky2)
{
	unsigned size;

	/* Space needed for frame data + headers rounded up */
	size = roundup(sky2->netdev->mtu + ETH_HLEN + VLAN_HLEN, 8);

	/* Stopping point for hardware truncation */
	return (size - 8) / sizeof(u32);
}