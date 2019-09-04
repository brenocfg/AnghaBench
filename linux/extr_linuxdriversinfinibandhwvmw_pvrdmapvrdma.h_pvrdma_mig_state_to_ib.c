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
typedef  enum pvrdma_mig_state { ____Placeholder_pvrdma_mig_state } pvrdma_mig_state ;
typedef  enum ib_mig_state { ____Placeholder_ib_mig_state } ib_mig_state ;

/* Variables and functions */

__attribute__((used)) static inline enum ib_mig_state pvrdma_mig_state_to_ib(
					enum pvrdma_mig_state state)
{
	return (enum ib_mig_state)state;
}