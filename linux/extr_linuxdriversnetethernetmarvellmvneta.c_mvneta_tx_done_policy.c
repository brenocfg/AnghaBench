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
struct mvneta_tx_queue {int dummy; } ;
struct mvneta_port {struct mvneta_tx_queue* txqs; } ;

/* Variables and functions */
 int fls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mvneta_tx_queue *mvneta_tx_done_policy(struct mvneta_port *pp,
						     u32 cause)
{
	int queue = fls(cause) - 1;

	return &pp->txqs[queue];
}