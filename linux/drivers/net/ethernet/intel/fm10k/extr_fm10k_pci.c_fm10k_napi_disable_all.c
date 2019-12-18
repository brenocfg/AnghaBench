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
struct fm10k_q_vector {int /*<<< orphan*/  napi; } ;
struct fm10k_intfc {int num_q_vectors; struct fm10k_q_vector** q_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm10k_napi_disable_all(struct fm10k_intfc *interface)
{
	struct fm10k_q_vector *q_vector;
	int q_idx;

	for (q_idx = 0; q_idx < interface->num_q_vectors; q_idx++) {
		q_vector = interface->q_vector[q_idx];
		napi_disable(&q_vector->napi);
	}
}