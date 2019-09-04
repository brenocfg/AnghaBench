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
struct mvneta_port {int /*<<< orphan*/ * txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_txq_deinit (struct mvneta_port*,int /*<<< orphan*/ *) ; 
 int txq_number ; 

__attribute__((used)) static void mvneta_cleanup_txqs(struct mvneta_port *pp)
{
	int queue;

	for (queue = 0; queue < txq_number; queue++)
		mvneta_txq_deinit(pp, &pp->txqs[queue]);
}