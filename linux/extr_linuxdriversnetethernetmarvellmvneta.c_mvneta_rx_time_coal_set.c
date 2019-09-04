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
typedef  unsigned long u32 ;
struct mvneta_rx_queue {int /*<<< orphan*/  id; } ;
struct mvneta_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_RXQ_TIME_COAL_REG (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void mvneta_rx_time_coal_set(struct mvneta_port *pp,
				    struct mvneta_rx_queue *rxq, u32 value)
{
	u32 val;
	unsigned long clk_rate;

	clk_rate = clk_get_rate(pp->clk);
	val = (clk_rate / 1000000) * value;

	mvreg_write(pp, MVNETA_RXQ_TIME_COAL_REG(rxq->id), val);
}