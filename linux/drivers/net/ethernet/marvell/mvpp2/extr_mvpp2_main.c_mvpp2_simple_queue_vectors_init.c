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
struct mvpp2_queue_vector {scalar_t__ irq; int /*<<< orphan*/  napi; struct mvpp2_port* port; int /*<<< orphan*/  sw_thread_mask; scalar_t__ sw_thread_id; int /*<<< orphan*/  type; int /*<<< orphan*/  nrxqs; scalar_t__ first_rxq; } ;
struct mvpp2_port {int nqvecs; int /*<<< orphan*/  dev; int /*<<< orphan*/  nrxqs; struct mvpp2_queue_vector* qvecs; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MVPP2_QUEUE_VECTOR_SHARED ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/ * cpumask_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_poll ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_simple_queue_vectors_init(struct mvpp2_port *port,
					   struct device_node *port_node)
{
	struct mvpp2_queue_vector *v = &port->qvecs[0];

	v->first_rxq = 0;
	v->nrxqs = port->nrxqs;
	v->type = MVPP2_QUEUE_VECTOR_SHARED;
	v->sw_thread_id = 0;
	v->sw_thread_mask = *cpumask_bits(cpu_online_mask);
	v->port = port;
	v->irq = irq_of_parse_and_map(port_node, 0);
	if (v->irq <= 0)
		return -EINVAL;
	netif_napi_add(port->dev, &v->napi, mvpp2_poll,
		       NAPI_POLL_WEIGHT);

	port->nqvecs = 1;

	return 0;
}