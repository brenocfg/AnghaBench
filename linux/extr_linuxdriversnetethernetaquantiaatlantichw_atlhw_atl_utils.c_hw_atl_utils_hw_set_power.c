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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_POWER ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_set_speed (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_set_state (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

int hw_atl_utils_hw_set_power(struct aq_hw_s *self,
			      unsigned int power_state)
{
	hw_atl_utils_mpi_set_speed(self, 0);
	hw_atl_utils_mpi_set_state(self, MPI_POWER);
	return 0;
}