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
struct sky2_port {unsigned int rx_nfrags; TYPE_1__* netdev; } ;
struct rx_ring_info {int /*<<< orphan*/  frag_addr; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int ETH_HLEN ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ VLAN_HLEN ; 
 unsigned int copybreak ; 
 unsigned int roundup (scalar_t__,int) ; 

__attribute__((used)) static unsigned sky2_get_rx_data_size(struct sky2_port *sky2)
{
	struct rx_ring_info *re;
	unsigned size;

	/* Space needed for frame data + headers rounded up */
	size = roundup(sky2->netdev->mtu + ETH_HLEN + VLAN_HLEN, 8);

	sky2->rx_nfrags = size >> PAGE_SHIFT;
	BUG_ON(sky2->rx_nfrags > ARRAY_SIZE(re->frag_addr));

	/* Compute residue after pages */
	size -= sky2->rx_nfrags << PAGE_SHIFT;

	/* Optimize to handle small packets and headers */
	if (size < copybreak)
		size = copybreak;
	if (size < ETH_HLEN)
		size = ETH_HLEN;

	return size;
}