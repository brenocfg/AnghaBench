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
typedef  int u32 ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ena_com_update_nonadaptive_moderation_interval(u32 coalesce_usecs,
							  u32 intr_delay_resolution,
							  u32 *intr_moder_interval)
{
	if (!intr_delay_resolution) {
		pr_err("Illegal interrupt delay granularity value\n");
		return -EFAULT;
	}

	*intr_moder_interval = coalesce_usecs / intr_delay_resolution;

	return 0;
}