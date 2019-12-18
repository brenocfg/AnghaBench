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
struct mvneta_rx_queue {int /*<<< orphan*/  id; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int MVNETA_RXQ_NON_OCCUPIED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_RXQ_THRESHOLD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvneta_rx_pkts_coal_set(struct mvneta_port *pp,
				    struct mvneta_rx_queue *rxq, u32 value)
{
	mvreg_write(pp, MVNETA_RXQ_THRESHOLD_REG(rxq->id),
		    value | MVNETA_RXQ_NON_OCCUPIED(0));
}