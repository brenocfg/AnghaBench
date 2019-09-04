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
 int cpu_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

int zip_get_node_id(void)
{
	return cpu_to_node(raw_smp_processor_id());
}