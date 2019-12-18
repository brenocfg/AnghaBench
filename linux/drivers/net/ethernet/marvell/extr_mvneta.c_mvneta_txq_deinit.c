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
struct mvneta_tx_queue {int dummy; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_txq_hw_deinit (struct mvneta_port*,struct mvneta_tx_queue*) ; 
 int /*<<< orphan*/  mvneta_txq_sw_deinit (struct mvneta_port*,struct mvneta_tx_queue*) ; 

__attribute__((used)) static void mvneta_txq_deinit(struct mvneta_port *pp,
			      struct mvneta_tx_queue *txq)
{
	mvneta_txq_sw_deinit(pp, txq);
	mvneta_txq_hw_deinit(pp, txq);
}