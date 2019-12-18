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
struct hfi1_pportdata {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 char** state_complete_reasons ; 

__attribute__((used)) static const char *state_complete_reason_code_string(struct hfi1_pportdata *ppd,
						     u32 code)
{
	const char *str = NULL;

	if (code < ARRAY_SIZE(state_complete_reasons))
		str = state_complete_reasons[code];

	if (str)
		return str;
	return "Reserved";
}