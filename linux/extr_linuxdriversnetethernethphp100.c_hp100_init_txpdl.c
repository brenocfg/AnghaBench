#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * skb; int /*<<< orphan*/  pdl_paddr; int /*<<< orphan*/ * pdl; } ;
typedef  TYPE_1__ hp100_ring_t ;

/* Variables and functions */
 int MAX_TX_FRAG ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  virt_to_whatever (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp100_init_txpdl(struct net_device *dev,
			    register hp100_ring_t * ringptr,
			    register u32 * pdlptr)
{
	if (0 != (((unsigned long) pdlptr) & 0xf))
		printk("hp100: %s: Init txpdl: Unaligned pdlptr 0x%lx.\n", dev->name, (unsigned long) pdlptr);

	ringptr->pdl = pdlptr;	/* +1; */
	ringptr->pdl_paddr = virt_to_whatever(dev, pdlptr);	/* +1 */
	ringptr->skb = NULL;

	return roundup(MAX_TX_FRAG * 2 + 2, 4);
}