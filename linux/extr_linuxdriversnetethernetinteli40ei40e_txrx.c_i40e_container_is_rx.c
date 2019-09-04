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
struct i40e_ring_container {int dummy; } ;
struct i40e_q_vector {struct i40e_ring_container rx; } ;

/* Variables and functions */

__attribute__((used)) static inline bool i40e_container_is_rx(struct i40e_q_vector *q_vector,
					struct i40e_ring_container *rc)
{
	return &q_vector->rx == rc;
}