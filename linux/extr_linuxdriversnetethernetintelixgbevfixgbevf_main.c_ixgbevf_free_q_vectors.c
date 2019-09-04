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
struct ixgbevf_adapter {int num_msix_vectors; } ;

/* Variables and functions */
 int NON_Q_VECTORS ; 
 int /*<<< orphan*/  ixgbevf_free_q_vector (struct ixgbevf_adapter*,int) ; 

__attribute__((used)) static void ixgbevf_free_q_vectors(struct ixgbevf_adapter *adapter)
{
	int q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;

	while (q_vectors) {
		q_vectors--;
		ixgbevf_free_q_vector(adapter, q_vectors);
	}
}