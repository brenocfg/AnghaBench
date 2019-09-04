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
 unsigned int X86_BR_CALL_STACK ; 
 unsigned int X86_BR_USER ; 

__attribute__((used)) static inline bool branch_user_callstack(unsigned br_sel)
{
	return (br_sel & X86_BR_USER) && (br_sel & X86_BR_CALL_STACK);
}