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
struct igb_q_vector {int dummy; } ;
struct igb_adapter {struct igb_q_vector** q_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct igb_q_vector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void igb_free_q_vector(struct igb_adapter *adapter, int v_idx)
{
	struct igb_q_vector *q_vector = adapter->q_vector[v_idx];

	adapter->q_vector[v_idx] = NULL;

	/* igb_get_stats64() might access the rings on this vector,
	 * we must wait a grace period before freeing it.
	 */
	if (q_vector)
		kfree_rcu(q_vector, rcu);
}