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
struct mvpp2_queue_vector {int sw_thread_id; int first_rxq; int nrxqs; int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; int /*<<< orphan*/  type; int /*<<< orphan*/  sw_thread_mask; struct mvpp2_port* port; } ;
struct mvpp2_port {int nqvecs; int nrxqs; struct mvpp2_queue_vector* qvecs; int /*<<< orphan*/  dev; int /*<<< orphan*/  fwnode; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  irqname ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int MVPP2_DEFAULT_RXQ ; 
 scalar_t__ MVPP2_QDIST_MULTI_MODE ; 
 scalar_t__ MVPP2_QDIST_SINGLE_MODE ; 
 int /*<<< orphan*/  MVPP2_QUEUE_VECTOR_PRIVATE ; 
 int /*<<< orphan*/  MVPP2_QUEUE_VECTOR_SHARED ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  fwnode_irq_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_poll ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_possible_cpus () ; 
 int /*<<< orphan*/  of_irq_get_byname (struct device_node*,char*) ; 
 scalar_t__ queue_mode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int mvpp2_multi_queue_vectors_init(struct mvpp2_port *port,
					  struct device_node *port_node)
{
	struct mvpp2_queue_vector *v;
	int i, ret;

	port->nqvecs = num_possible_cpus();
	if (queue_mode == MVPP2_QDIST_SINGLE_MODE)
		port->nqvecs += 1;

	for (i = 0; i < port->nqvecs; i++) {
		char irqname[16];

		v = port->qvecs + i;

		v->port = port;
		v->type = MVPP2_QUEUE_VECTOR_PRIVATE;
		v->sw_thread_id = i;
		v->sw_thread_mask = BIT(i);

		snprintf(irqname, sizeof(irqname), "tx-cpu%d", i);

		if (queue_mode == MVPP2_QDIST_MULTI_MODE) {
			v->first_rxq = i * MVPP2_DEFAULT_RXQ;
			v->nrxqs = MVPP2_DEFAULT_RXQ;
		} else if (queue_mode == MVPP2_QDIST_SINGLE_MODE &&
			   i == (port->nqvecs - 1)) {
			v->first_rxq = 0;
			v->nrxqs = port->nrxqs;
			v->type = MVPP2_QUEUE_VECTOR_SHARED;
			strncpy(irqname, "rx-shared", sizeof(irqname));
		}

		if (port_node)
			v->irq = of_irq_get_byname(port_node, irqname);
		else
			v->irq = fwnode_irq_get(port->fwnode, i);
		if (v->irq <= 0) {
			ret = -EINVAL;
			goto err;
		}

		netif_napi_add(port->dev, &v->napi, mvpp2_poll,
			       NAPI_POLL_WEIGHT);
	}

	return 0;

err:
	for (i = 0; i < port->nqvecs; i++)
		irq_dispose_mapping(port->qvecs[i].irq);
	return ret;
}