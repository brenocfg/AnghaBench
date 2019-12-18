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
typedef  int u32 ;
struct mvpp2_queue_vector {int nrxqs; int sw_thread_id; int first_rxq; } ;
struct mvpp2_port {int id; int nrxqs; int nqvecs; struct mvpp2_queue_vector* qvecs; struct mvpp2* priv; } ;
struct mvpp2 {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 int /*<<< orphan*/  MVPP21_ISR_RXQ_GROUP_REG (int) ; 
 int MVPP22_ISR_RXQ_GROUP_INDEX_GROUP_OFFSET ; 
 int /*<<< orphan*/  MVPP22_ISR_RXQ_GROUP_INDEX_REG ; 
 int /*<<< orphan*/  MVPP22_ISR_RXQ_SUB_GROUP_CONFIG_REG ; 
 int MVPP22_ISR_RXQ_SUB_GROUP_SIZE_OFFSET ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp2_rx_irqs_setup(struct mvpp2_port *port)
{
	struct mvpp2 *priv = port->priv;
	u32 val;
	int i;

	if (priv->hw_version == MVPP21) {
		mvpp2_write(priv, MVPP21_ISR_RXQ_GROUP_REG(port->id),
			    port->nrxqs);
		return;
	}

	/* Handle the more complicated PPv2.2 case */
	for (i = 0; i < port->nqvecs; i++) {
		struct mvpp2_queue_vector *qv = port->qvecs + i;

		if (!qv->nrxqs)
			continue;

		val = qv->sw_thread_id;
		val |= port->id << MVPP22_ISR_RXQ_GROUP_INDEX_GROUP_OFFSET;
		mvpp2_write(priv, MVPP22_ISR_RXQ_GROUP_INDEX_REG, val);

		val = qv->first_rxq;
		val |= qv->nrxqs << MVPP22_ISR_RXQ_SUB_GROUP_SIZE_OFFSET;
		mvpp2_write(priv, MVPP22_ISR_RXQ_SUB_GROUP_CONFIG_REG, val);
	}
}