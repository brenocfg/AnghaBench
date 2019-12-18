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
struct ravb_private {int /*<<< orphan*/  rx_fifo_errors; TYPE_1__* stats; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_over_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIS ; 
 int EIS_QFS ; 
 int EIS_RESERVED ; 
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 int /*<<< orphan*/  RIS2 ; 
 int RIS2_QFF0 ; 
 int RIS2_QFF1 ; 
 int RIS2_RESERVED ; 
 int RIS2_RFFF ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ravb_error_interrupt(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	u32 eis, ris2;

	eis = ravb_read(ndev, EIS);
	ravb_write(ndev, ~(EIS_QFS | EIS_RESERVED), EIS);
	if (eis & EIS_QFS) {
		ris2 = ravb_read(ndev, RIS2);
		ravb_write(ndev, ~(RIS2_QFF0 | RIS2_RFFF | RIS2_RESERVED),
			   RIS2);

		/* Receive Descriptor Empty int */
		if (ris2 & RIS2_QFF0)
			priv->stats[RAVB_BE].rx_over_errors++;

		    /* Receive Descriptor Empty int */
		if (ris2 & RIS2_QFF1)
			priv->stats[RAVB_NC].rx_over_errors++;

		/* Receive FIFO Overflow int */
		if (ris2 & RIS2_RFFF)
			priv->rx_fifo_errors++;
	}
}