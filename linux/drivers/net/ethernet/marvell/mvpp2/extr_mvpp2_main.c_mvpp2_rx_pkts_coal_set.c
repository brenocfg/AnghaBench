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
struct mvpp2_rx_queue {scalar_t__ pkts_coal; scalar_t__ id; } ;
struct mvpp2_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 scalar_t__ MVPP2_OCCUPIED_THRESH_MASK ; 
 int /*<<< orphan*/  MVPP2_RXQ_NUM_REG ; 
 int /*<<< orphan*/  MVPP2_RXQ_THRESH_REG ; 
 int /*<<< orphan*/  get_cpu () ; 
 unsigned int mvpp2_cpu_to_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_thread_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static void mvpp2_rx_pkts_coal_set(struct mvpp2_port *port,
				   struct mvpp2_rx_queue *rxq)
{
	unsigned int thread = mvpp2_cpu_to_thread(port->priv, get_cpu());

	if (rxq->pkts_coal > MVPP2_OCCUPIED_THRESH_MASK)
		rxq->pkts_coal = MVPP2_OCCUPIED_THRESH_MASK;

	mvpp2_thread_write(port->priv, thread, MVPP2_RXQ_NUM_REG, rxq->id);
	mvpp2_thread_write(port->priv, thread, MVPP2_RXQ_THRESH_REG,
			   rxq->pkts_coal);

	put_cpu();
}