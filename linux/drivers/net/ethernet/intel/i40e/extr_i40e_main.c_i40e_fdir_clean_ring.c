#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {int /*<<< orphan*/  work_limit; } ;
struct TYPE_3__ {TYPE_2__* ring; } ;
struct i40e_q_vector {TYPE_1__ tx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  i40e_clean_fdir_tx_irq (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t i40e_fdir_clean_ring(int irq, void *data)
{
	struct i40e_q_vector *q_vector = data;
	struct i40e_vsi *vsi;

	if (!q_vector->tx.ring)
		return IRQ_HANDLED;

	vsi = q_vector->tx.ring->vsi;
	i40e_clean_fdir_tx_irq(q_vector->tx.ring, vsi->work_limit);

	return IRQ_HANDLED;
}