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
struct dpaa2_io {int dummy; } ;

/* Variables and functions */
 int DPAA2_IO_ANY_CPU ; 
 struct dpaa2_io* service_select (int /*<<< orphan*/ *) ; 
 struct dpaa2_io* service_select_by_cpu (int /*<<< orphan*/ *,int) ; 

struct dpaa2_io *dpaa2_io_service_select(int cpu)
{
	if (cpu == DPAA2_IO_ANY_CPU)
		return service_select(NULL);

	return service_select_by_cpu(NULL, cpu);
}