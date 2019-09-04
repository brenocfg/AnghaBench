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
struct mvneta_rx_queue {int /*<<< orphan*/  id; } ;
struct mvneta_port {TYPE_1__* pool_long; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_RXQ_CONFIG_REG (int /*<<< orphan*/ ) ; 
 int MVNETA_RXQ_LONG_POOL_ID_MASK ; 
 int MVNETA_RXQ_LONG_POOL_ID_SHIFT ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvneta_rxq_long_pool_set(struct mvneta_port *pp,
				     struct mvneta_rx_queue *rxq)
{
	u32 val;

	val = mvreg_read(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val &= ~MVNETA_RXQ_LONG_POOL_ID_MASK;
	val |= (pp->pool_long->id << MVNETA_RXQ_LONG_POOL_ID_SHIFT);

	mvreg_write(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
}