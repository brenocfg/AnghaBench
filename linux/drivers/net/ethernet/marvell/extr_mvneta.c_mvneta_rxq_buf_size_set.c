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
 int MVNETA_RXQ_BUF_SIZE_MASK ; 
 int MVNETA_RXQ_BUF_SIZE_SHIFT ; 
 int /*<<< orphan*/  MVNETA_RXQ_SIZE_REG (int /*<<< orphan*/ ) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvneta_rxq_buf_size_set(struct mvneta_port *pp,
				    struct mvneta_rx_queue *rxq,
				    int buf_size)
{
	u32 val;

	val = mvreg_read(pp, MVNETA_RXQ_SIZE_REG(rxq->id));

	val &= ~MVNETA_RXQ_BUF_SIZE_MASK;
	val |= ((buf_size >> 3) << MVNETA_RXQ_BUF_SIZE_SHIFT);

	mvreg_write(pp, MVNETA_RXQ_SIZE_REG(rxq->id), val);
}