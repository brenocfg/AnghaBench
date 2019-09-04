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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int GPIO_ENUM_UNKNOWN ; 

__attribute__((used)) static uint32_t index_from_vector(
	uint32_t vector)
{
	uint32_t result = 0;
	uint32_t mask = 1;

	do {
		if (vector == mask)
			return result;

		++result;
		mask <<= 1;
	} while (mask);

	BREAK_TO_DEBUGGER();

	return GPIO_ENUM_UNKNOWN;
}