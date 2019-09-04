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
 unsigned int FAULT_CODE_ITLB ; 
 unsigned int FAULT_CODE_WRITE ; 

__attribute__((used)) static inline unsigned int
expevt_to_fault_code(unsigned long expevt)
{
	if (expevt == 0xa40)
		return FAULT_CODE_ITLB;
	else if (expevt == 0x060)
		return FAULT_CODE_WRITE;

	return 0;
}