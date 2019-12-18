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
 unsigned int num_possible_cpus () ; 
 unsigned int poll_queues ; 
 unsigned int write_queues ; 

__attribute__((used)) static unsigned int max_io_queues(void)
{
	return num_possible_cpus() + write_queues + poll_queues;
}