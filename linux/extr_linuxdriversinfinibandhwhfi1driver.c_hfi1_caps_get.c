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
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 unsigned long HFI1_CAP_K2U ; 
 unsigned long HFI1_CAP_LOCKED_SMASK ; 
 unsigned long HFI1_CAP_USER_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int hfi1_caps_get(char *buffer, const struct kernel_param *kp)
{
	unsigned long cap_mask = *(unsigned long *)kp->arg;

	cap_mask &= ~HFI1_CAP_LOCKED_SMASK;
	cap_mask |= ((cap_mask & HFI1_CAP_K2U) << HFI1_CAP_USER_SHIFT);

	return scnprintf(buffer, PAGE_SIZE, "0x%lx", cap_mask);
}