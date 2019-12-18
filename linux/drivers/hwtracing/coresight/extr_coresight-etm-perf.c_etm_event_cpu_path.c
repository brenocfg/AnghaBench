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
struct etm_event_data {int dummy; } ;

/* Variables and functions */
 struct list_head** etm_event_cpu_path_ptr (struct etm_event_data*,int) ; 

__attribute__((used)) static inline struct list_head *
etm_event_cpu_path(struct etm_event_data *data, int cpu)
{
	return *etm_event_cpu_path_ptr(data, cpu);
}