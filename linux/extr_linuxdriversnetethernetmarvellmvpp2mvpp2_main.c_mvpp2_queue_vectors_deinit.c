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
struct mvpp2_port {int nqvecs; TYPE_1__* qvecs; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_queue_vectors_deinit(struct mvpp2_port *port)
{
	int i;

	for (i = 0; i < port->nqvecs; i++)
		irq_dispose_mapping(port->qvecs[i].irq);
}