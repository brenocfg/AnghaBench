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
 int VMCI_PRIVILEGE_FLAG_RESTRICTED ; 
 int VMCI_PRIVILEGE_FLAG_TRUSTED ; 

__attribute__((used)) static inline bool vmci_deny_interaction(u32 part_one, u32 part_two)
{
	return ((part_one & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
		!(part_two & VMCI_PRIVILEGE_FLAG_TRUSTED)) ||
	       ((part_two & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
		!(part_one & VMCI_PRIVILEGE_FLAG_TRUSTED));
}