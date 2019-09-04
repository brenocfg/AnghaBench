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

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  local_daif_mask () ; 
 int /*<<< orphan*/  sdei_mask_local_cpu () ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 

__attribute__((used)) static void ipi_cpu_stop(unsigned int cpu)
{
	set_cpu_online(cpu, false);

	local_daif_mask();
	sdei_mask_local_cpu();

	while (1)
		cpu_relax();
}