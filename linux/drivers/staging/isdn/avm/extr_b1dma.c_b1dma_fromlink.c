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
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ avmcard ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  b1dma_rx_full (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  t1inp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int b1dma_fromlink(avmcard *card, void *buf, unsigned int len)
{
	unsigned long stop = jiffies + 1 * HZ;	/* maximum wait time 1 sec */
	unsigned char *s = (unsigned char *)buf;
	while (len--) {
		while (!b1dma_rx_full(card->port)
		       && time_before(jiffies, stop));
		if (!b1dma_rx_full(card->port))
			return -1;
		*s++ = t1inp(card->port, 0x00);
	}
	return 0;
}