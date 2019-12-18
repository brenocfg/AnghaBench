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
struct bnxt {int flags; TYPE_1__* dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int BNXT_FLAG_GRO ; 
 int BNXT_FLAG_LRO ; 
 int BNXT_FLAG_NO_AGG_RINGS ; 
 int BNXT_FLAG_TPA ; 
 int NETIF_F_GRO_HW ; 
 int NETIF_F_LRO ; 

void bnxt_set_tpa_flags(struct bnxt *bp)
{
	bp->flags &= ~BNXT_FLAG_TPA;
	if (bp->flags & BNXT_FLAG_NO_AGG_RINGS)
		return;
	if (bp->dev->features & NETIF_F_LRO)
		bp->flags |= BNXT_FLAG_LRO;
	else if (bp->dev->features & NETIF_F_GRO_HW)
		bp->flags |= BNXT_FLAG_GRO;
}