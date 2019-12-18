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
struct list_head {int dummy; } ;
struct etm_event_data {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct list_head** per_cpu_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct list_head **
etm_event_cpu_path_ptr(struct etm_event_data *data, int cpu)
{
	return per_cpu_ptr(data->path, cpu);
}