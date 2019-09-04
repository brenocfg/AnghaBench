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
struct ldc_packet {int dummy; } ;
struct ldc_channel {int tx_tail; unsigned long tx_head; struct ldc_packet* tx_base; } ;

/* Variables and functions */
 int LDC_PACKET_SIZE ; 
 unsigned long tx_advance (struct ldc_channel*,int) ; 

__attribute__((used)) static struct ldc_packet *handshake_get_tx_packet(struct ldc_channel *lp,
						  unsigned long *new_tail)
{
	struct ldc_packet *p;
	unsigned long t;

	t = tx_advance(lp, lp->tx_tail);
	if (t == lp->tx_head)
		return NULL;

	*new_tail = t;

	p = lp->tx_base;
	return p + (lp->tx_tail / LDC_PACKET_SIZE);
}