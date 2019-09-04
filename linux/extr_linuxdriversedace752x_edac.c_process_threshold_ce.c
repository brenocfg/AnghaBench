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
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  e752x_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void process_threshold_ce(struct mem_ctl_info *mci, u16 error,
					int *error_found, int handle_error)
{
	*error_found = 1;

	if (handle_error)
		e752x_mc_printk(mci, KERN_WARNING, "Memory threshold CE\n");
}