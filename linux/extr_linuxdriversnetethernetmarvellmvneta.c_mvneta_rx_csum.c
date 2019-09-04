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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; scalar_t__ csum; } ;
struct mvneta_port {TYPE_1__* dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int MVNETA_RXD_L3_IP4 ; 
 int MVNETA_RXD_L4_CSUM_OK ; 
 int NETIF_F_RXCSUM ; 

__attribute__((used)) static void mvneta_rx_csum(struct mvneta_port *pp, u32 status,
			   struct sk_buff *skb)
{
	if ((pp->dev->features & NETIF_F_RXCSUM) &&
	    (status & MVNETA_RXD_L3_IP4) &&
	    (status & MVNETA_RXD_L4_CSUM_OK)) {
		skb->csum = 0;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		return;
	}

	skb->ip_summed = CHECKSUM_NONE;
}