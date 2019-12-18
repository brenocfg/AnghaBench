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
 int MVNETA_RXQ_OCCUPIED_ALL_MASK ; 
 int /*<<< orphan*/  MVNETA_RXQ_STATUS_REG (int /*<<< orphan*/ ) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvneta_rxq_busy_desc_num_get(struct mvneta_port *pp,
					struct mvneta_rx_queue *rxq)
{
	u32 val;

	val = mvreg_read(pp, MVNETA_RXQ_STATUS_REG(rxq->id));
	return val & MVNETA_RXQ_OCCUPIED_ALL_MASK;
}