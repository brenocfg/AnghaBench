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
typedef  scalar_t__ u32 ;
struct mvpp2_rx_queue {int /*<<< orphan*/  id; int /*<<< orphan*/  time_coal; } ;
struct mvpp2_port {TYPE_1__* priv; } ;
struct TYPE_2__ {unsigned long tclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_ISR_RX_THRESHOLD_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ MVPP2_MAX_ISR_RX_THRESHOLD ; 
 int /*<<< orphan*/  mvpp2_cycles_to_usec (scalar_t__,unsigned long) ; 
 scalar_t__ mvpp2_usec_to_cycles (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mvpp2_write (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvpp2_rx_time_coal_set(struct mvpp2_port *port,
				   struct mvpp2_rx_queue *rxq)
{
	unsigned long freq = port->priv->tclk;
	u32 val = mvpp2_usec_to_cycles(rxq->time_coal, freq);

	if (val > MVPP2_MAX_ISR_RX_THRESHOLD) {
		rxq->time_coal =
			mvpp2_cycles_to_usec(MVPP2_MAX_ISR_RX_THRESHOLD, freq);

		/* re-evaluate to get actual register value */
		val = mvpp2_usec_to_cycles(rxq->time_coal, freq);
	}

	mvpp2_write(port->priv, MVPP2_ISR_RX_THRESHOLD_REG(rxq->id), val);
}