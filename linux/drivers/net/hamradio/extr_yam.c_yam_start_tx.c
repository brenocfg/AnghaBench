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
struct yam_port {scalar_t__ tx_state; int txd; int tx_count; int bitrate; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TX_HEAD ; 
 scalar_t__ TX_TAIL ; 
 int /*<<< orphan*/  ptt_on (struct net_device*) ; 

__attribute__((used)) static void yam_start_tx(struct net_device *dev, struct yam_port *yp)
{
	if ((yp->tx_state == TX_TAIL) || (yp->txd == 0))
		yp->tx_count = 1;
	else
		yp->tx_count = (yp->bitrate * yp->txd) / 8000;
	yp->tx_state = TX_HEAD;
	ptt_on(dev);
}