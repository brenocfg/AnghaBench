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
struct TYPE_2__ {int /*<<< orphan*/  affinity_mask; } ;
struct aq_vec_s {TYPE_1__ aq_ring_param; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */

cpumask_t *aq_vec_get_affinity_mask(struct aq_vec_s *self)
{
	return &self->aq_ring_param.affinity_mask;
}