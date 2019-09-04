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
struct cr_regs {int cam; } ;

/* Variables and functions */
 int EINVAL ; 
 int MMU_CAM_V ; 

__attribute__((used)) static inline int iotlb_cr_valid(struct cr_regs *cr)
{
	if (!cr)
		return -EINVAL;

	return cr->cam & MMU_CAM_V;
}