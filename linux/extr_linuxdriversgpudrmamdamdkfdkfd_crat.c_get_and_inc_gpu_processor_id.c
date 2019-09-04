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
 unsigned int gpu_processor_id_low ; 

__attribute__((used)) static inline unsigned int get_and_inc_gpu_processor_id(
				unsigned int total_cu_count)
{
	int current_id = gpu_processor_id_low;

	gpu_processor_id_low += total_cu_count;
	return current_id;
}