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
struct fault_info {int dummy; } ;

/* Variables and functions */
 struct fault_info const* fault_info ; 

__attribute__((used)) static inline const struct fault_info *esr_to_fault_info(unsigned int esr)
{
	return fault_info + (esr & 63);
}