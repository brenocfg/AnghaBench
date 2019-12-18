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
struct sk_buff {unsigned char* data; } ;
struct dbdma_cmd {int dummy; } ;

/* Variables and functions */
 int INPUT_LAST ; 
 int INTR_ALWAYS ; 
 int /*<<< orphan*/  RX_BUFLEN ; 
 unsigned char* bmac_emergency_rxbuf ; 
 int /*<<< orphan*/  dbdma_setcmd (struct dbdma_cmd volatile*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (unsigned char*) ; 

__attribute__((used)) static void
bmac_construct_rxbuff(struct sk_buff *skb, volatile struct dbdma_cmd *cp)
{
	unsigned char *addr = skb? skb->data: bmac_emergency_rxbuf;

	dbdma_setcmd(cp, (INPUT_LAST | INTR_ALWAYS), RX_BUFLEN,
		     virt_to_bus(addr), 0);
}