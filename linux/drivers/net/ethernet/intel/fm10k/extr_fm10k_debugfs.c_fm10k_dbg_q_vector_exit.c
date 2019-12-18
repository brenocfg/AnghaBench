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
struct fm10k_q_vector {int /*<<< orphan*/ * dbg_q_vector; struct fm10k_intfc* interface; } ;
struct fm10k_intfc {scalar_t__ dbg_intfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void fm10k_dbg_q_vector_exit(struct fm10k_q_vector *q_vector)
{
	struct fm10k_intfc *interface = q_vector->interface;

	if (interface->dbg_intfc)
		debugfs_remove_recursive(q_vector->dbg_q_vector);
	q_vector->dbg_q_vector = NULL;
}