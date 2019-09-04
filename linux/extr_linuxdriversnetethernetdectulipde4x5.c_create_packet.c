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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 

__attribute__((used)) static void
create_packet(struct net_device *dev, char *frame, int len)
{
    int i;
    char *buf = frame;

    for (i=0; i<ETH_ALEN; i++) {             /* Use this source address */
	*buf++ = dev->dev_addr[i];
    }
    for (i=0; i<ETH_ALEN; i++) {             /* Use this destination address */
	*buf++ = dev->dev_addr[i];
    }

    *buf++ = 0;                              /* Packet length (2 bytes) */
    *buf++ = 1;
}