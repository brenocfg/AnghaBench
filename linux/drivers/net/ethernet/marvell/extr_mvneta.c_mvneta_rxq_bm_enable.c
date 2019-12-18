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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_rx_queue {int /*<<< orphan*/  id; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_RXQ_CONFIG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_RXQ_HW_BUF_ALLOC ; 
 int /*<<< orphan*/  mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_rxq_bm_enable(struct mvneta_port *pp,
				 struct mvneta_rx_queue *rxq)
{
	u32 val;

	val = mvreg_read(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val |= MVNETA_RXQ_HW_BUF_ALLOC;
	mvreg_write(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
}