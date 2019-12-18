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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 

__attribute__((used)) static const char *state_completed_string(u32 completed)
{
	static const char * const state_completed[] = {
		"EstablishComm",
		"OptimizeEQ",
		"VerifyCap"
	};

	if (completed < ARRAY_SIZE(state_completed))
		return state_completed[completed];

	return "unknown";
}