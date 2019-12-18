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
typedef  int u_int ;
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int* pdl; int /*<<< orphan*/ * skb; scalar_t__ pdl_paddr; } ;
typedef  TYPE_1__ hp100_ring_t ;

/* Variables and functions */
 int MAX_RX_FRAG ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int roundup (int,int) ; 
 scalar_t__ virt_to_whatever (struct net_device*,int*) ; 

__attribute__((used)) static int hp100_init_rxpdl(struct net_device *dev,
			    register hp100_ring_t * ringptr,
			    register u32 * pdlptr)
{
	/* pdlptr is starting address for this pdl */

	if (0 != (((unsigned long) pdlptr) & 0xf))
		printk("hp100: %s: Init rxpdl: Unaligned pdlptr 0x%lx.\n",
		       dev->name, (unsigned long) pdlptr);

	ringptr->pdl = pdlptr + 1;
	ringptr->pdl_paddr = virt_to_whatever(dev, pdlptr + 1);
	ringptr->skb = NULL;

	/*
	 * Write address and length of first PDL Fragment (which is used for
	 * storing the RX-Header
	 * We use the 4 bytes _before_ the PDH in the pdl memory area to
	 * store this information. (PDH is at offset 0x04)
	 */
	/* Note that pdlptr+1 and not pdlptr is the pointer to the PDH */

	*(pdlptr + 2) = (u_int) virt_to_whatever(dev, pdlptr);	/* Address Frag 1 */
	*(pdlptr + 3) = 4;	/* Length  Frag 1 */

	return roundup(MAX_RX_FRAG * 2 + 2, 4);
}