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
typedef  size_t u32 ;
struct gve_tx_ring {TYPE_1__* q_resources; } ;
struct gve_priv {int /*<<< orphan*/ * counter_array; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  counter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 

__be32 gve_tx_load_event_counter(struct gve_priv *priv,
				 struct gve_tx_ring *tx)
{
	u32 counter_index = be32_to_cpu((tx->q_resources->counter_index));

	return READ_ONCE(priv->counter_array[counter_index]);
}