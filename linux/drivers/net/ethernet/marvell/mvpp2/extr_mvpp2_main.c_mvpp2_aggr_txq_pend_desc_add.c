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
struct mvpp2_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_AGGR_TXQ_UPDATE_REG ; 
 int /*<<< orphan*/  mvpp2_cpu_to_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_thread_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void mvpp2_aggr_txq_pend_desc_add(struct mvpp2_port *port, int pending)
{
	/* aggregated access - relevant TXQ number is written in TX desc */
	mvpp2_thread_write(port->priv,
			   mvpp2_cpu_to_thread(port->priv, smp_processor_id()),
			   MVPP2_AGGR_TXQ_UPDATE_REG, pending);
}