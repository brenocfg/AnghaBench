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
struct gfar_private {int num_rx_queues; int /*<<< orphan*/  ndev; TYPE_1__** rx_queue; } ;
struct gfar_priv_rx_q {int dummy; } ;
struct TYPE_2__ {int qindex; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfar_alloc_rx_queues(struct gfar_private *priv)
{
	int i;

	for (i = 0; i < priv->num_rx_queues; i++) {
		priv->rx_queue[i] = kzalloc(sizeof(struct gfar_priv_rx_q),
					    GFP_KERNEL);
		if (!priv->rx_queue[i])
			return -ENOMEM;

		priv->rx_queue[i]->qindex = i;
		priv->rx_queue[i]->ndev = priv->ndev;
	}
	return 0;
}