#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int dev_flags; int dev_devwidth; } ;
typedef  TYPE_1__ dbdev_tab_t ;
struct TYPE_4__ {TYPE_1__* chan_dest; TYPE_1__* chan_src; } ;
typedef  TYPE_2__ chan_tab_t ;

/* Variables and functions */
 int DEV_FLAGS_IN ; 
 int DEV_FLAGS_OUT ; 

u32 au1xxx_dbdma_set_devwidth(u32 chanid, int bits)
{
	u32		rv;
	chan_tab_t	*ctp;
	dbdev_tab_t	*stp, *dtp;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_src;
	dtp = ctp->chan_dest;
	rv = 0;

	if (stp->dev_flags & DEV_FLAGS_IN) {	/* Source in fifo */
		rv = stp->dev_devwidth;
		stp->dev_devwidth = bits;
	}
	if (dtp->dev_flags & DEV_FLAGS_OUT) {	/* Destination out fifo */
		rv = dtp->dev_devwidth;
		dtp->dev_devwidth = bits;
	}

	return rv;
}