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
struct net_device {char* dev_addr; } ;
struct de4x5_private {char* setup_frame; scalar_t__ setup_f; } ;

/* Variables and functions */
 int ALL ; 
 int DE4X5_HASH_TABLE_LEN ; 
 int ETH_ALEN ; 
 scalar_t__ HASH_PERF ; 
 int IMPERF_PA_OFFSET ; 
 int /*<<< orphan*/  SETUP_FRAME_LEN ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static char *
build_setup_frame(struct net_device *dev, int mode)
{
    struct de4x5_private *lp = netdev_priv(dev);
    int i;
    char *pa = lp->setup_frame;

    /* Initialise the setup frame */
    if (mode == ALL) {
	memset(lp->setup_frame, 0, SETUP_FRAME_LEN);
    }

    if (lp->setup_f == HASH_PERF) {
	for (pa=lp->setup_frame+IMPERF_PA_OFFSET, i=0; i<ETH_ALEN; i++) {
	    *(pa + i) = dev->dev_addr[i];                 /* Host address */
	    if (i & 0x01) pa += 2;
	}
	*(lp->setup_frame + (DE4X5_HASH_TABLE_LEN >> 3) - 3) = 0x80;
    } else {
	for (i=0; i<ETH_ALEN; i++) { /* Host address */
	    *(pa + (i&1)) = dev->dev_addr[i];
	    if (i & 0x01) pa += 4;
	}
	for (i=0; i<ETH_ALEN; i++) { /* Broadcast address */
	    *(pa + (i&1)) = (char) 0xff;
	    if (i & 0x01) pa += 4;
	}
    }

    return pa;                     /* Points to the next entry */
}